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

    /**
     * @brief Gets the name of the aircraft.
     * @return Aircraft name
     */
    inline std::string name() const
    {
      return m_name;
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

    Engine::Physics::BoundingBoxShape *m_colShapeBody; //!< Collision shape for main body
    Engine::Physics::BoundingBoxShape *m_colShapeTail; //!< Collision shape for tail/boom
    btCylinderShape *m_colShapeMainRotor;              //!< Collision shape for main rotor
    btCylinderShape *m_colShapeTailRotor;              //!< Collision shape for tail rotor

    Engine::Audio::Source *m_soundEngine;    //!< Background sound caused by motor/mehanics
    Engine::Audio::Source *m_soundMainRotor; //!< Air sound caused by pitching the main rotor
    Engine::Audio::Source *m_soundTailRotor; //!< Air sound caused by running tail rotor
    Engine::Audio::Source *m_soundCrash;     //!< Sound of the aircraft colliding with something
  };
}
}

#endif