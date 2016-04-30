/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_ITELEMETRYPROTOCOL_H_
#define _GAMEDEV_FLIGHTSIM_ITELEMETRYPROTOCOL_H_

#include <map>

namespace GameDev
{
namespace FlightSim
{
  /**
   * @brief Represents a telemetry sensor.
   * @author Dan Nixon
   */
  enum class TelemetryValue : size_t
  {
    RSSI,
    VBAT,
    ALTITUDE,
    VERT_SPEED
  };

  /**
   * @class ITelemetryProtocol
   * @brief Abstract class for a telemetry protocol.
   * @author Dan Nixon
   */
  class ITelemetryProtocol
  {
  public:
    ITelemetryProtocol()
    {
    }

    virtual ~ITelemetryProtocol()
    {
    }

    /**
     * @brief Sets a sensor value.
     * @param telem Sensor type
     * @param value Value
     */
    void setValue(TelemetryValue telem, float value)
    {
      m_values[telem] = value;
    }

    /**
     * @brief Gets the value of a sensor.
     * @param telem Sensor type
     * @return Value
     */
    float value(TelemetryValue telem)
    {
      return m_values[telem];
    }

    /**
     * @brief Sends the telemetry values using the current protocol.
     * @return True if transmission was successful
     */
    virtual bool send() = 0;

  protected:
    std::map<TelemetryValue, float> m_values; //!< Sensor values
  };
}
}

#endif
