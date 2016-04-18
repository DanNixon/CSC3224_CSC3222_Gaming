/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _GAMEDEV_DEMO_AIRCRAFT_H_
#define _GAMEDEV_DEMO_AIRCRAFT_H_

#include <Engine_Common/SceneObject.h>

#include <Engine_Audio/Source.h>
#include <Engine_Physics/PhysicalSystem.h>

namespace GameDev
{
namespace Demo
{
  enum AircraftModel : size_t
  {
    BODY,
    MAIN_ROTOR_SPIN,
    TAIL_ROTOR_SPIN
  };

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
  class Aircraft : public Engine::Common::SceneObject
  {
  public:
    Aircraft(const std::string &name, const std::string &resourceRoot = "../resources/");
    virtual ~Aircraft();

    std::string modelFilename(AircraftModel model) const;
    std::string audioFilename(AircraftSound sound) const;

    bool loadMeshes();
    bool initPhysics(Engine::Physics::PhysicalSystem *system, const Engine::Maths::Vector3 &initialPosition,
                     const Engine::Maths::Quaternion &initialRotation);
    bool loadAudio(Engine::Audio::Listener *listener);

    /**
     * @brief Gets the source of a given type of sound.
     * @param sound Sound type
     * @return Pointer to the sound source
     */
    inline Engine::Audio::Source *audioSource(AircraftSound sound)
    {
      return m_sounds[sound];
    }

    inline void setThrust(float thrust)
    {
      m_mainRotorThrust = thrust;
    }

    inline void setAxisRates(const Engine::Maths::Vector3 &rates)
    {
      m_axisRates = rates;
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
     * @brief Gets the receiver signal strength indicator value in dB.
     * @return RSSI
     */
    inline int rssi() const
    {
      return m_rssi;
    }

    /**
     * @brief Gets the altitude of the aircraft above the terrain origin in
     *        feet.
     * @return Altitude (ft)
     */
    inline float altitude() const
    {
      return m_altitudeFeet;
    }

    /**
     * @brief Gets the battery voltage of the aircraft.
     * @return Battery voltage
     */
    inline float batteryVoltage() const
    {
      return m_batteryVolts;
    }

    void setEngineSpeed(float speed);
    void setControls(float throttle, float pitch, float roll, float yaw);

  protected:
    std::string m_resourceRoot; //!< Path to the root of the resources directory

    float m_mass;                       //!< Mass in g
    float m_mainRotorThrust;            //!< Main rotor lifting force at maximum RPM and maximum throttle
    Engine::Maths::Vector3 m_axisRates; //!< Rate coefficients for rotation in each axis

    float m_engineSpeed;  //!< Engine/motor speed (factor of max RPM)
    int m_rssi;           //!< RSSI in dB
    float m_altitudeFeet; //!< Altitude in feet relative to Y=0
    float m_batteryVolts; //!< Battery voltage

    Engine::Common::SceneObject *m_subTreeAircraft;          //!< Scene sub tree containing main aircraft
    Engine::Common::SceneObject *m_subTreeMainRotor;         //!< Scene sub tree containing static main rotor
    Engine::Common::SceneObject *m_subTreeTailRotor;         //!< Scene sub tree containing static tail rotor
    Engine::Common::SceneObject *m_subTreeSpinningMainRotor; //!< Scene sub tree containing spinning main rotor
    Engine::Common::SceneObject *m_subTreeSpinningTailRotor; //!< Scene sub tree containing spinning tail rotor

    Engine::Physics::RigidBody *m_physicalBody; //!< Phsyical body of the aircraft

    Engine::Audio::Source *m_sounds[4]; //!< Pointers to each type of sound emitted from the aircraft
  };
}
}

#endif