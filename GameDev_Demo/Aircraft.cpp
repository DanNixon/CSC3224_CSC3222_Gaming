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
#include <Engine_Physics/BoundingBoxShape.h>
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
      , m_mass(1.0f)
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

    ModelLoader bodyLoader;
    m_subTreeAircraft =
        bodyLoader.load(modelFilename(AircraftModel::BODY), ShaderProgramLookup::Instance().get("aircraft_shader"));
    addChild(m_subTreeAircraft);

    // ModelLoader mainRotorLoader;
    // m_subTreeSpinningMainRotor = mainRotorLoader.load(modelFilename(AircraftModel::MAIN_ROTOR_SPIN), m_shaders);
    // addChild(m_subTreeSpinningMainRotor);

    // ModelLoader tailRotorLoader;
    // m_subTreeSpinningTailRotor = tailRotorLoader.load(modelFilename(AircraftModel::TAIL_ROTOR_SPIN), m_shaders);
    // addChild(m_subTreeSpinningTailRotor);

    return result;
  }

  bool Aircraft::initPhysics(PhysicalSystem *system, const Vector3 &initialPosition, const Quaternion &initialRotation)
  {
    bool result = true;

    // Collision shape
    btCompoundShape *shape = new btCompoundShape();

    // TODO
    BoundingBoxShape *bodyBBox = new BoundingBoxShape();
    bodyBBox->updateDimensionFromSceneTree(m_subTreeAircraft);
    // shape->addChildShape(btTransform(), bodyBBox);

    // Motion
    SceneObjectMotionState *motion = new SceneObjectMotionState(this, initialPosition, initialRotation);

    // Body
    m_physicalBody = new RigidBody(motion, m_mass, btVector3(0.0f, 0.0f, 0.0f), bodyBBox);
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

  /**
   * @brief Sets the aircraft engine speed.
   * @param speed Speed in interval [0.0,1.0]
   * @see Aircraft::setControls()
   *
   * This would be equivalent of the throttle on a helicopter.
   */
  void Aircraft::setEngineSpeed(float speed)
  {
    bool engineOn = speed > 0.01f;

    // Update engine idle sound
    if (engineOn)
    {
      if (!m_sounds[AircraftSound::ENGINE_IDLE]->isPlaying())
        m_sounds[AircraftSound::ENGINE_IDLE]->play();

      m_sounds[AircraftSound::ENGINE_IDLE]->setGain(5.0f * (speed * 75.0f));
      m_sounds[AircraftSound::ENGINE_IDLE]->setPitch(0.8f + (speed * 0.2f));
    }
    else
    {
      m_sounds[AircraftSound::ENGINE_IDLE]->stop();
    }

    m_engineSpeed = speed;
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
    Vector3 axisVector(pitch, roll, yaw);
    axisVector = axisVector * m_axisRates * m_engineSpeed;

    // Orientation
    btTransform trans = m_physicalBody->body()->getWorldTransform();
    btQuaternion angularOffset;
    angularOffset.setEuler(axisVector.z(), axisVector.y(), axisVector.x());
    btQuaternion angle = trans.getRotation() * angularOffset;
    trans.setRotation(angle);

    // Thrust
    btVector3 thrust(0.0f, m_mainRotorThrust * m_engineSpeed * throttle, 0.0f);
    // TODO: rotate thrust vector

    m_physicalBody->body()->setWorldTransform(trans);
    m_physicalBody->body()->applyCentralForce(thrust);
  }
}
}