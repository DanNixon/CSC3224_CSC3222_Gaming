/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_AIRCRAFT_H_
#define _GAMEDEV_FLIGHTSIM_AIRCRAFT_H_

#include <Engine_Common/SceneObject.h>

#include <Engine_Audio/Source.h>
#include <Engine_Common/Game.h>
#include <Engine_Graphics/Camera.h>
#include <Engine_Graphics/RenderableObject.h>
#include <Engine_IO/INIKeyValueStore.h>
#include <Engine_Maths/VectorOperations.h>
#include <Engine_Physics/CollisionCallback.h>
#include <Engine_Physics/PhysicalSystem.h>

namespace GameDev
{
namespace FlightSim
{
  /**
   * @brief Used to identify models for an aircraft.
   * @author Dan Nixon
   */
  enum AircraftModel : size_t
  {
    BODY,
    MAIN_ROTOR_SPIN,
    TAIL_ROTOR_SPIN
  };

  /**
   * @brief Used to identify a sound made by an aircraft.
   * @author Dan Nixon
   */
  enum AircraftSound : size_t
  {
    ENGINE_IDLE,
    MAIN_ROTOR,
    TAIL_ROTOR,
    CRASH
  };

  /**
   * @class Aircraft
   * @brief Class containing all information about an aircraft.
   * @author Dan Nixon
   */
  class Aircraft : public Engine::Common::SceneObject, public Engine::IO::INIKeyValueStore
  {
  public:
    Aircraft(const std::string &name, const std::string &resourceRoot);
    virtual ~Aircraft();

    std::string metadataFilename() const;
    std::string modelFilename(AircraftModel model) const;
    std::string audioFilename(AircraftSound sound) const;

    void loadMetadata();
    void loadMeshes();
    void initPhysics(const Engine::Maths::Vector3 &initialPosition, const Engine::Maths::Quaternion &initialRotation);
    bool loadAudio(Engine::Audio::Listener *listener);
    void initCamera(Engine::Common::Game *game, float viewDepth = 1000.0f, float fieldOfVision = 45.0f);

    inline void addToSystem(Engine::Physics::PhysicalSystem *system)
    {
      system->addBody(m_physicalBody);
      system->addBody(m_mainRotorBody);
      system->addBody(m_tailRotorBody);
    }

    inline void removeFromSystem(Engine::Physics::PhysicalSystem *system)
    {
      system->removeBody(m_physicalBody);
      system->removeBody(m_mainRotorBody);
      system->removeBody(m_tailRotorBody);
    }

    /**
     * @brief Gets the source of a given type of sound.
     * @param sound Sound type
     * @return Pointer to the sound source
     */
    inline Engine::Audio::Source *audioSource(AircraftSound sound)
    {
      return m_sounds[sound];
    }

    inline std::string displayName() const
    {
      return m_displayName;
    }

    /**
     * @brief Gets the mass of the aircraft in g.
     * @return Aircraft mass
     */
    inline float mass() const
    {
      return m_mass;
    }

    /**
     * @brief Calculates a very rough estimation of the  the receiver signal strength indicator value in dB.
     * @return RSSI
     */
    inline int rssi() const
    {
      float rssi =
          (Engine::Maths::VectorOperations::Distance2(m_worldTransform.positionVector(), Engine::Maths::Vector3()) -
           m_rssiMinDist2) *
          m_rssiInverseRange2;

      return (int)((1.0f - Engine::Maths::Constrain(rssi, 0.0f, 1.0f)) * 110.0f);
    }

    /**
     * @brief Calculates the altitude of the aircraft above the terrain origin.
     * @return Altitude (m)
     */
    inline float altitude() const
    {
      return m_modelMatrix.positionVector()[1] * 0.01f;
    }

    /**
     * @brief Gets the battery voltage of the aircraft.
     * @return Battery voltage
     */
    inline float batteryVoltage() const
    {
      return m_batteryVolts;
    }

    /**
     * @brief Calculates a very rough approximate current draw from the model battery.
     * @return Current (A)
     */
    inline float batteryCurrent() const
    {
      if (m_batteryVolts < 0.1f)
        return 0.0f;

      return ((m_engineSpeed * (std::abs(m_collective * 0.8f) + 0.2f) * m_maxMotorPower) + m_baselinePower) /
             m_batteryVolts;
    }

    /**
     * @brief Gets the first person view camera.
     * @return Pointer to the FPV camera
     */
    inline Engine::Graphics::Camera *fpvCamera()
    {
      return m_fpvCamera;
    }

    void setEngineSpeed(float speed);
    void setControls(float throttle, float pitch, float roll, float yaw);

    void reset();
    void activateFailsafe();

    virtual void update(float msec, Engine::Common::Subsystem sys);

  protected:
    std::string m_resourceRoot; //!< Path to the root of the resources directory

    std::string m_displayName;
    float m_mass;                       //!< Mass in g
    float m_mainRotorThrust;            //!< Main rotor lifting force at maximum RPM and maximum throttle
    Engine::Maths::Vector3 m_axisRates; //!< Rate coefficients for rotation in each axis (roll, yaw, pitch)
    float m_baselinePower;
    float m_maxMotorPower;
    float m_rssiMinDist2;
    float m_rssiInverseRange2;
    float m_fullBatteryVolts;
    float m_emptyBatteryVolts;
    float m_magicBatteryDischargeCoeff;

    bool m_failsafe;      //!< Flag indicating a failsafe condition
    float m_engineSpeed;  //!< Engine/motor speed (factor of max RPM)
    float m_collective;   //!< Collective pitch
    float m_batteryVolts; //!< Battery voltage

    Engine::Graphics::RenderableObject *m_subTreeAircraft;          //!< Scene sub tree containing main aircraft
    Engine::Graphics::RenderableObject *m_subTreeMainRotor;         //!< Scene sub tree containing static main rotor
    Engine::Graphics::RenderableObject *m_subTreeTailRotor;         //!< Scene sub tree containing static tail rotor
    Engine::Graphics::RenderableObject *m_subTreeSpinningMainRotor; //!< Scene sub tree containing spinning main rotor
    Engine::Graphics::RenderableObject *m_subTreeSpinningTailRotor; //!< Scene sub tree containing spinning tail rotor

    Engine::Physics::RigidBody *m_physicalBody; //!< Physical body of the aircraft
    Engine::Physics::RigidBody *m_mainRotorBody;
    Engine::Physics::RigidBody *m_tailRotorBody;
    Engine::Maths::Quaternion m_initialRotation; //!< Initial orientation of the aircraft model
    Engine::Maths::Vector3 m_initialPosition;    //!< Initial world position of the aircraft model

    Engine::Audio::Source *m_sounds[4]; //!< Pointers to each type of sound emitted from the aircraft

    Engine::Graphics::Camera *m_fpvCamera; //!< First person view camera
  };
}
}

#endif
