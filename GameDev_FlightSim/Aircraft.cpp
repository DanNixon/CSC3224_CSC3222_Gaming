/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "Aircraft.h"

#include <sstream>

#include <Engine_Audio/WAVSource.h>
#include <Engine_Graphics/ModelLoader.h>
#include <Engine_Graphics/ShaderProgram.h>
#include <Engine_Logging/Logger.h>
#include <Engine_Physics/BoundingCylinderShape.h>
#include <Engine_Physics/MathsConversions.h>
#include <Engine_Physics/SceneObjectMotionState.h>
#include <Engine_Utility/StringUtils.h>

using namespace Engine::Common;
using namespace Engine::Audio;
using namespace Engine::Graphics;
using namespace Engine::Utility;
using namespace Engine::Maths;
using namespace Engine::Physics;

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

namespace GameDev
{
namespace FlightSim
{
  /**
   * @brief Creates a new aircraft.
   * @param name Name of the aircraft (must match directory in model directory)
   * @param resourceRoot Root of the resources directory
   */
  Aircraft::Aircraft(const std::string &name, const std::string &resourceRoot)
      : SceneObject(name)
      , m_resourceRoot(resourceRoot)
      , m_mass(0.0f)
      , m_mainRotorThrust(0.0f)
      , m_axisRates()
      , m_failsafe(false)
      , m_batteryVolts(0.0f)
      , m_physicalBody(nullptr)
  {
    for (size_t i = 0; i < 4; i++)
      m_sounds[i] = nullptr;
  }

  Aircraft::~Aircraft()
  {
  }

  std::string Aircraft::metadataFilename() const
  {
    std::stringstream str;
    str << m_resourceRoot << m_name << "/" << m_name << ".ini";
    return str.str();
  }

  /**
   * @brief Gets the filename of a model.
   * @param model Model type
   * @return File path
   */
  std::string Aircraft::modelFilename(AircraftModel model) const
  {
    std::stringstream str;
    str << m_resourceRoot << m_name << "/";

    switch (model)
    {
    case AircraftModel::BODY:
      str << m_name;
      break;
    case AircraftModel::MAIN_ROTOR_SPIN:
      str << "Mainrotor";
      break;
    case AircraftModel::TAIL_ROTOR_SPIN:
      str << "Tailrotor";
      break;
    }

    str << ".obj";

    return str.str();
  }

  /**
   * @brief Gets the filename of a sound file.
   * @param sound Sound type
   * @return File path
   */
  std::string Aircraft::audioFilename(AircraftSound sound) const
  {
    std::stringstream str;
    str << m_resourceRoot << m_name << "/";

    switch (sound)
    {
    case AircraftSound::ENGINE_IDLE:
      str << m_name;
      break;
    case AircraftSound::MAIN_ROTOR:
      str << "blade";
      break;
    case AircraftSound::TAIL_ROTOR:
      str << "tail";
      break;
    case AircraftSound::CRASH:
      str << ""; //!< \todo
      break;
    }

    str << ".wav";

    return str.str();
  }

  void Aircraft::loadMetadata()
  {
    // Load data
    std::ifstream file(metadataFilename());
    load(file);

    // Skip loading if this model is not enabled
    if (!m_rootKVNode.child("general").keyBool("enabled"))
      return;

    // Parse member data
    m_displayName = m_rootKVNode.child("general").keyString("name");
    m_mass = m_rootKVNode.child("dynamics").keyFloat("mass");
    m_mainRotorThrust = m_rootKVNode.child("dynamics").keyFloat("main_rotor_thrust");
    m_axisRates = m_rootKVNode.child("dynamics").keyVector3("axis_rates");
    m_fullBatteryVolts = m_rootKVNode.child("avionics").keyFloat("battery_full_v");
    m_emptyBatteryVolts = m_rootKVNode.child("avionics").keyFloat("battery_empty_v");
    m_magicBatteryDischargeCoeff = m_rootKVNode.child("avionics").keyFloat("battery_discharge_coeff");
    m_baselinePower = m_rootKVNode.child("avionics").keyFloat("avionics_power_w");
    m_maxMotorPower = m_rootKVNode.child("avionics").keyFloat("motor_power_w");
    m_rssiMinDist2 = std::pow(m_rootKVNode.child("avionics").keyFloat("rssi_min_range_m") * 10.0f, 2);
    m_rssiInverseRange2 =
        1.0f / (std::pow(m_rootKVNode.child("avionics").keyFloat("rssi_max_range_m") * 10.0f, 2) - m_rssiMinDist2);
  }

  /**
   * @brief Loads all meshes unsed by the aircraft.
   */
  void Aircraft::loadMeshes()
  {
    // Do not load multiple times
    if (m_subTreeAircraft != nullptr)
      return;

    // Main model
    ModelLoader bodyLoader;
    m_subTreeAircraft =
        bodyLoader.load(modelFilename(AircraftModel::BODY), ShaderProgramLookup::Instance().get("aircraft_shader_lit"));
    m_subTreeAircraft->setModelMatrix(Matrix4::Scale(2.0f));
    addChild(m_subTreeAircraft);

    // Static main rotor
    m_subTreeMainRotor = dynamic_cast<RenderableObject *>(m_subTreeAircraft->find("g Mainrotor_0"));
    if (m_subTreeMainRotor == nullptr)
      g_log.error("Could not find main rotor mesh");

    // Static tail rotor
    m_subTreeTailRotor = dynamic_cast<RenderableObject *>(m_subTreeAircraft->find("g Tailrotor_0"));
    if (m_subTreeTailRotor == nullptr)
      g_log.error("Could not find tail rotor mesh");

    // Spinning main rotor
    ModelLoader mainRotorLoader;
    m_subTreeSpinningMainRotor = mainRotorLoader.load(modelFilename(AircraftModel::MAIN_ROTOR_SPIN),
                                                      ShaderProgramLookup::Instance().get("aircraft_shader_tex"));
    m_subTreeSpinningMainRotor->setModelMatrix(Matrix4::Scale(2.0f));
    m_subTreeSpinningMainRotor->setActive(false);
    m_subTreeSpinningMainRotor->setTransparent(true, std::numeric_limits<size_t>::max());
    addChild(m_subTreeSpinningMainRotor);

    // Spinning tail rotor
    ModelLoader tailRotorLoader;
    m_subTreeSpinningTailRotor = tailRotorLoader.load(modelFilename(AircraftModel::TAIL_ROTOR_SPIN),
                                                      ShaderProgramLookup::Instance().get("aircraft_shader_tex"));
    m_subTreeSpinningTailRotor->setModelMatrix(Matrix4::Translation(Vector3(-74.0f, 0.0f, 1.5f)) *
                                               Matrix4::Rotation(90.0f, Vector3(1.0f, 0.0f, 0.0f)) *
                                               Matrix4::Scale(0.4f));
    m_subTreeSpinningTailRotor->setActive(false);
    m_subTreeSpinningTailRotor->setTransparent(true, std::numeric_limits<size_t>::max());
    addChild(m_subTreeSpinningTailRotor);
  }

  /**
   * @brief Configures physics objects.
   * @param initialPosition Initial position of the aircraft
   * @param initialRotation Initial orientation of the aircraft
   */
  void Aircraft::initPhysics(const Vector3 &initialPosition, const Quaternion &initialRotation)
  {
    // Do not init multiple times
    if (m_physicalBody != nullptr)
      return;

    // Record initial state
    m_initialRotation = initialRotation;
    m_initialPosition = initialPosition;

    // Collision shape
    btCompoundShape *shape = new btCompoundShape();

    // Main body bounding box
    btBoxShape *bodyBox =
        new btBoxShape(MathsConversions::ToBullet(m_rootKVNode.children()["physics"].keyVector3("body_aabb")));
    shape->addChildShape(
        btTransform(btQuaternion(0.0f, 0.0f, 0.0f),
                    MathsConversions::ToBullet(m_rootKVNode.children()["physics"].keyVector3("body_aabb_pos"))),
        bodyBox);

    // Tail/boom bounding box
    btBoxShape *tailBox =
        new btBoxShape(MathsConversions::ToBullet(m_rootKVNode.children()["physics"].keyVector3("tail_aabb")));
    shape->addChildShape(
        btTransform(btQuaternion(0.0f, 0.0f, 0.0f),
                    MathsConversions::ToBullet(m_rootKVNode.children()["physics"].keyVector3("tail_aabb_pos"))),
        tailBox);

    // Motion
    SceneObjectMotionState *motion = new SceneObjectMotionState(this, initialPosition, initialRotation);

    // Aircraft body
    m_physicalBody = new RigidBody(motion, m_mass, btVector3(0.0f, 0.0f, 0.0f), shape);
    m_physicalBody->body()->setActivationState(DISABLE_DEACTIVATION);

    // Main rotor cylinder
    BoundingCylinderShape *mainRotorCylinder = new BoundingCylinderShape();
    mainRotorCylinder->updateDimensionFromSceneTree(m_subTreeSpinningMainRotor);

    // Main rotor body
    m_mainRotorBody = new RigidBody(new btDefaultMotionState(), 0.0f, btVector3(0.0f, 0.0f, 0.0f), mainRotorCylinder);
    m_mainRotorBody->body()->setActivationState(DISABLE_DEACTIVATION);
    m_mainRotorBody->body()->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

    // Tail rotor cylinder
    BoundingCylinderShape *tailRotorCylinder = new BoundingCylinderShape();
    tailRotorCylinder->updateDimensionFromSceneTree(m_subTreeSpinningTailRotor);

    // Tail rotor body
    m_tailRotorBody = new RigidBody(new btDefaultMotionState(), 0.0f, btVector3(0.0f, 0.0f, 0.0f), tailRotorCylinder);
    m_tailRotorBody->body()->setActivationState(DISABLE_DEACTIVATION);
    m_tailRotorBody->body()->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
  }

  /**
   * @brief Loads audio files.
   * @param listener Audio listener in use
   * @return True if files were laoded successfully
   */
  bool Aircraft::loadAudio(Listener *listener)
  {
    bool result = true;

    //!< \todo change 3 -> 4 when crash sound is added
    for (size_t i = 0; i < 3; i++)
    {
      // Do not load multiple times
      if (m_sounds[i] != nullptr)
        continue;

      std::string filename = audioFilename(static_cast<AircraftSound>(i));
      std::string name = StringUtils::BasenameFromFilename(StringUtils::FilenameFromPath(filename));

      WAVSource *s = new WAVSource(name, listener);

      if (s->load(filename))
      {
        s->setLooping(true);
        m_sounds[i] = s;
        addChild(s);
      }
      else
      {
        result = false;
      }
    }

    return result;
  }

  /**
   * @brief Configures the first person view camera.
   * @param game Game in use
   * @param viewDepth View depth
   * @param fieldOfVision Field of view angle in degrees
   */
  void Aircraft::initCamera(Game *game, float viewDepth, float fieldOfVision)
  {
    // Do not init multiple times
    if (m_fpvCamera != nullptr)
      return;

    m_fpvCamera = new Camera("fpv_camera", Matrix4::Perspective(1.0f, viewDepth, game->windowAspect(), fieldOfVision));
    m_fpvCamera->setActive(false);
    m_fpvCamera->setModelMatrix(Matrix4::Translation(m_rootKVNode.child("camera").keyVector3("fpv_camera_pos")));
    addChild(m_fpvCamera);

    // TODO: use angle
    // m_rootKVNode.child("camera").keyFloat("fpv_camera_angle")
  }

  /**
   * @brief Sets the aircraft engine speed.
   * @param speed Speed in interval [0.0,1.0]
   * @see Aircraft::setControls()
   *
   * This would be equivalent of the throttle on a helicopter.
   */
  void Aircraft::setEngineSpeed(float speed)
  {
    // Clamp to interval [0,1]
    if (m_failsafe)
      m_engineSpeed = 0.0f;
    else
      m_engineSpeed = std::max(std::min(speed, 1.0f), 0.0f);

    bool engineOn = m_engineSpeed > 0.01f;

    // Update fast rotating rotor meshes
    bool aboveRotorPOVSpeed = speed >= 0.2f;
    m_subTreeSpinningMainRotor->setActive(aboveRotorPOVSpeed);
    m_subTreeSpinningTailRotor->setActive(aboveRotorPOVSpeed);
    m_subTreeMainRotor->setActive(!aboveRotorPOVSpeed);
    m_subTreeTailRotor->setActive(!aboveRotorPOVSpeed);

    // Update engine idle sound
    if (engineOn)
    {
      if (!m_sounds[AircraftSound::ENGINE_IDLE]->isPlaying())
        m_sounds[AircraftSound::ENGINE_IDLE]->play();

      m_sounds[AircraftSound::ENGINE_IDLE]->setGain(2.0f * (m_engineSpeed * 10.0f));
      m_sounds[AircraftSound::ENGINE_IDLE]->setPitch(0.8f + (m_engineSpeed * 0.2f));
    }
    else
    {
      m_sounds[AircraftSound::ENGINE_IDLE]->stop();
    }
  }

  /**
   * @brief Sets the control surfaces of the aircraft.
   * @param throttle Throttle position
   * @param pitch Pitch rate
   * @param roll Roll rate
   * @param yaw Yaw rate
   * @see Aircraft::setEngineSpeed()
   *
   * All controls are in interval [-1,1].
   *
   * For a helicopter throttle is equivalent to the collective pitch, pitch
   * and roll are the cyclic and yaw is tail rotor.
   */
  void Aircraft::setControls(float throttle, float pitch, float roll, float yaw)
  {
    if (m_failsafe)
      return;

    m_collective = throttle;

    // Adjust rotation by rates and engine (rotor) speed
    Vector3 axisVector(roll, yaw, pitch);
    axisVector = axisVector * m_axisRates * m_engineSpeed;

    // Rotation
    btTransform transform = m_physicalBody->body()->getWorldTransform();
    Quaternion rotation = MathsConversions::FromBullet(transform.getRotation());
    axisVector = rotation.rotateVector(axisVector);
    m_physicalBody->body()->setAngularVelocity(MathsConversions::ToBullet(axisVector));

    // Thrust
    btVector3 thrust = m_physicalBody->upVector() * m_mainRotorThrust * m_engineSpeed * throttle;
    m_physicalBody->body()->applyCentralForce(thrust);
  }

  /**
   * @brief Resets the aircraft to the default state.
   */
  void Aircraft::reset()
  {
    // Reset failsafe flag
    m_failsafe = false;

    // Reset battery
    m_batteryVolts = m_fullBatteryVolts;

    // Reset controls
    setEngineSpeed(0.0f);
    setControls(0.0f, 0.0f, 0.0f, 0.0f);

    // Set initial orientation and position
    m_physicalBody->body()->clearForces();
    m_physicalBody->body()->setCenterOfMassTransform(MathsConversions::ToBullet(m_initialRotation, m_initialPosition));
  }

  /**
   * @brief Triggers the failsafe state.
   *
   * Calls to setEngineSpeed() and setControls() are ignored and the aircraft
   * behaves as though it has lost power.
   */
  void Aircraft::activateFailsafe()
  {
    m_failsafe = true;
    setEngineSpeed(0.0f);
  }

  /**
   * @copydoc SceneObject::update
   */
  void Aircraft::update(float msec, Subsystem sys)
  {
    SceneObject::update(msec, sys);

    if (sys == Subsystem::GRAPHICS)
    {
      m_fpvCamera->look(m_worldTransform.facingVector());
    }
    else if (sys == Subsystem::PHYSICS)
    {
      // Set main rotor collider position
      btTransform mainRotor;
      mainRotor.setFromOpenGLMatrix((const btScalar *)&(m_subTreeSpinningMainRotor->worldTransform()));
      // m_mainRotorBody->motionState()->setWorldTransform(mainRotor);
      m_mainRotorBody->body()->setWorldTransform(mainRotor);

      // Set tail rotor collider position
      btTransform tailRotor;
      tailRotor.setFromOpenGLMatrix((const btScalar *)&(m_subTreeSpinningTailRotor->worldTransform()));
      // m_tailRotorBody->motionState()->setWorldTransform(tailRotor);
      m_tailRotorBody->body()->setWorldTransform(tailRotor);

      // Simulate decreasing battery voltage
      m_batteryVolts -= batteryCurrent() * m_magicBatteryDischargeCoeff;

      // Trigger failsafe on dead battery
      if (m_batteryVolts <= m_emptyBatteryVolts)
        activateFailsafe();
    }
  }
}
}
