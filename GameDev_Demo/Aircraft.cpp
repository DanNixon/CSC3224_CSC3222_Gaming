/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
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
namespace Demo
{
  Aircraft::Aircraft(const std::string &name, const std::string &resourceRoot)
      : SceneObject(name)
      , m_resourceRoot(resourceRoot)
      , m_mass(0.6f)
      , m_mainRotorThrust(1.0f)
      , m_axisRates(1.0f, 1.0f, 1.0f)
      , m_rssi(0)
      , m_altitudeFeet(0.0f)
      , m_batteryVolts(12.6f)
      , m_physicalBody(nullptr)
  {
    for (size_t i = 0; i < 4; i++)
      m_sounds[i] = nullptr;
  }

  Aircraft::~Aircraft()
  {
  }

  std::string Aircraft::modelFilename(AircraftModel model) const
  {
    std::stringstream str;
    str << m_resourceRoot << "models/" << m_name << "/";

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

  std::string Aircraft::audioFilename(AircraftSound sound) const
  {
    std::stringstream str;
    str << m_resourceRoot << "models/" << m_name << "/";

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
      str << ""; // TODO
      break;
    }

    str << ".wav";

    return str.str();
  }

  bool Aircraft::loadMeshes()
  {
    bool result = true;

    // TODO: seemingly magic numbers here vary depending on the aircraft model
    //       and will be loaded from a file in the finished game.

    // Main model
    ModelLoader bodyLoader;
    m_subTreeAircraft =
        bodyLoader.load(modelFilename(AircraftModel::BODY), ShaderProgramLookup::Instance().get("aircraft_shader"));
    m_subTreeAircraft->setModelMatrix(Matrix4::Scale(2.0f));
    addChild(m_subTreeAircraft);

    // Spinning main rotor
    ModelLoader mainRotorLoader;
    m_subTreeSpinningMainRotor = mainRotorLoader.load(modelFilename(AircraftModel::MAIN_ROTOR_SPIN),
                                                      ShaderProgramLookup::Instance().get("aircraft_shader"));
    m_subTreeSpinningMainRotor->setModelMatrix(Matrix4::Scale(2.0f));
    m_subTreeSpinningMainRotor->setActive(false, std::numeric_limits<size_t>::max());
    addChild(m_subTreeSpinningMainRotor);

    // Spinning tail rotor
    ModelLoader tailRotorLoader;
    m_subTreeSpinningTailRotor = tailRotorLoader.load(modelFilename(AircraftModel::TAIL_ROTOR_SPIN),
                                                      ShaderProgramLookup::Instance().get("aircraft_shader"));
    m_subTreeSpinningTailRotor->setModelMatrix(Matrix4::Translation(Vector3(-74.0f, 0.0f, 1.5f)) *
                                               Matrix4::Rotation(90.0f, Vector3(1.0f, 0.0f, 0.0f)) *
                                               Matrix4::Scale(0.4f));
    m_subTreeSpinningTailRotor->setActive(false, std::numeric_limits<size_t>::max());
    addChild(m_subTreeSpinningTailRotor);

    return result;
  }

  bool Aircraft::initPhysics(PhysicalSystem *system, const Vector3 &initialPosition, const Quaternion &initialRotation)
  {
    bool result = true;

    // Collision shape
    btCompoundShape *shape = new btCompoundShape();

    // Main body bounding box
    btBoxShape *bodyBox = new btBoxShape(btVector3(20.0f, 10.0f, 10.0f));
    shape->addChildShape(btTransform(btQuaternion(0.0f, 0.0f, 0.0f), btVector3(5.0f, -5.0f, 0.0f)), bodyBox);

    // Tail/boom bounding box
    btBoxShape *tailBox = new btBoxShape(btVector3(40.0f, 5.0f, 5.0f));
    shape->addChildShape(btTransform(btQuaternion(0.0f, 0.0f, 0.0f), btVector3(-40.0f, 0.0f, 0.0f)), tailBox);

    // Main rotor cylinder
    BoundingCylinderShape *mainRotorCylinder = new BoundingCylinderShape();
    mainRotorCylinder->updateDimensionFromSceneTree(m_subTreeSpinningMainRotor);
    shape->addChildShape(
        btTransform(btQuaternion(0.0f, 0.0f, 0.0f), MathsConversions::ToBullet(mainRotorCylinder->origin())),
        mainRotorCylinder);

    // Tail rotor cylinder
    BoundingCylinderShape *tailRotorCylinder = new BoundingCylinderShape();
    tailRotorCylinder->updateDimensionFromSceneTree(m_subTreeSpinningTailRotor);
    shape->addChildShape(MathsConversions::ToBullet(Quaternion(0.0f, 90.0f, 0.0f), Vector3(-74.0f, 0.0f, 1.5f)),
                         tailRotorCylinder);

    // Motion
    SceneObjectMotionState *motion = new SceneObjectMotionState(this, initialPosition, initialRotation);

    // Body
    m_physicalBody = new RigidBody(motion, m_mass, btVector3(0.0f, 0.0f, 0.0f), shape);
    m_physicalBody->body()->setActivationState(DISABLE_DEACTIVATION);

    // Add to system
    system->addBody(m_physicalBody);

    return result;
  }

  bool Aircraft::loadAudio(Listener *listener)
  {
    bool result = true;

    // TODO: change 3 -> 4 when crash sound is added
    for (size_t i = 0; i < 3; i++)
    {
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

  void Aircraft::initCamera(Game *game, float viewDepth, float fieldOfVision)
  {
    m_fpvCamera = new Camera("fpv_camera", Matrix4::Perspective(1.0f, viewDepth, game->windowAspect(), fieldOfVision));
    m_fpvCamera->setActive(false);
    m_fpvCamera->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f)));
    addChild(m_fpvCamera);
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
    m_engineSpeed = std::max(std::min(speed, 1.0f), 0.0f);

    bool engineOn = m_engineSpeed > 0.01f;

    // Update fast rotating rotor meshes
    bool aboveRotorPOVSpeed = speed >= 0.2f;
    m_subTreeSpinningMainRotor->setActive(aboveRotorPOVSpeed, std::numeric_limits<size_t>::max());
    m_subTreeSpinningTailRotor->setActive(aboveRotorPOVSpeed, std::numeric_limits<size_t>::max());

    // Update engine idle sound
    if (engineOn)
    {
      if (!m_sounds[AircraftSound::ENGINE_IDLE]->isPlaying())
        m_sounds[AircraftSound::ENGINE_IDLE]->play();

      m_sounds[AircraftSound::ENGINE_IDLE]->setGain(5.0f * (m_engineSpeed * 75.0f));
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
}
}