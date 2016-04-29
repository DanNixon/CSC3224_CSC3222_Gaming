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
  enum class TelemetryValue : size_t
  {
    RSSI,
    VBAT,
    ALTITUDE
  };

  class ITelemetryProtocol
  {
  public:
    ITelemetryProtocol()
    {
    }

    virtual ~ITelemetryProtocol()
    {
    }

    void setValue(TelemetryValue telem, float value)
    {
      m_values[telem] = value;
    }

    float value(TelemetryValue telem)
    {
      return m_values[telem];
    }

  protected:
    std::map<TelemetryValue, float> m_values;
  };
}
}

#endif
