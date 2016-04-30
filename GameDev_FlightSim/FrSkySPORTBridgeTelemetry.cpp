/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "FrSkySPORTBridgeTelemetry.h"

#include <sstream>

namespace GameDev
{
namespace FlightSim
{
  FrSkySPORTBridgeTelemetry::FrSkySPORTBridgeTelemetry()
      : ITelemetryProtocol()
  {
    // Ensure all required values are present
    m_values[TelemetryValue::TELEM_OK] = 0.0f;
    m_values[TelemetryValue::RSSI] = 0.0f;
    m_values[TelemetryValue::CURRENT] = 0.0f;
    m_values[TelemetryValue::VBAT] = 0.0f;
    m_values[TelemetryValue::ALTITUDE] = 0.0f;
    m_values[TelemetryValue::VERT_SPEED] = 0.0f;
  }

  FrSkySPORTBridgeTelemetry::~FrSkySPORTBridgeTelemetry()
  {
  }

  bool FrSkySPORTBridgeTelemetry::send()
  {
    std::stringstream valuesStr;

    //!< \todo
    return false;
  }
}
}
