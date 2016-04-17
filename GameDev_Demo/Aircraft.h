/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _GAMEDEV_DEMO_AIRCRAFT_H_
#define _GAMEDEV_DEMO_AIRCRAFT_H_

#include <Engine_Common/SceneObject.h>

#include <btBulletDynamicsCommon.h>

#include <Engine_Audio/Source.h>
#include <Engine_Physics/BoundingBoxShape.h>

namespace GameDev
{
namespace Demo
{
  enum class AircraftModel : size_t
  {
    BODY,
    MAIN_ROTOR_SPIN,
    TAIL_ROTOR_SPIN
  };

  enum class AircraftSound : size_t
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
   *
   * TODO
   */
  class Aircraft : public Engine::Common::SceneObject
  {
  public:
    Aircraft(const std::string &name);
    virtual ~Aircraft();

    std::string modelFilename(AircraftModel model) const;
    std::string audioFilename(AircraftSound sound) const;

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

  protected:
    std::string m_name; //!< Name of the aircraft

    float m_mass;                       //!< Mass in g
    float m_mainRotorThrust;            //!< Maximum main rotor lifting force
    Engine::Maths::Vector3 m_axisRates; //!< Rate coefficients for rotation in each axis

    int m_rssi;           //!< RSSI in dB
    float m_altitudeFeet; //!< Altitude in feet relative to Y=0
    float m_batteryVolts; //!< Battery voltage

    Engine::Common::SceneObject *m_subTreeAircraft;          //!< Scene sub tree containing main aircraft
    Engine::Common::SceneObject *m_subTreeMainRotor;         //!< Scene sub tree containing static main rotor
    Engine::Common::SceneObject *m_subTreeTailRotor;         //!< Scene sub tree containing static tail rotor
    Engine::Common::SceneObject *m_subTreeSpinningMainRotor; //!< Scene sub tree containing spinning main rotor
    Engine::Common::SceneObject *m_subTreeSpinningTailRotor; //!< Scene sub tree containing spinning tail rotor

    btCompoundShape *m_collisionShape;

    Engine::Audio::Source *m_sounds[4];
  };
}
}

#endif