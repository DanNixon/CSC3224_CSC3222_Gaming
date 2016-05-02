/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "FrSkySPORTBridgeTelemetry.h"

#include <sstream>

#include <Engine_Logging/Logger.h>

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

namespace GameDev
{
namespace FlightSim
{
  FrSkySPORTBridgeTelemetry::FrSkySPORTBridgeTelemetry(SerialPort *port)
      : ITelemetryProtocol()
      , m_port(port)
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
    if (m_port == nullptr || !m_port->isOpen())
    {
      g_log.warn("Serial port not open, not sending telemetry data");
      return false;
    }

    // Build protocol string
    std::stringstream valuesStream;
    valuesStream << m_values[TelemetryValue::TELEM_OK] << ',' << m_values[TelemetryValue::RSSI] << ','
                 << m_values[TelemetryValue::CURRENT] << ',' << m_values[TelemetryValue::VBAT] << ','
                 << m_values[TelemetryValue::ALTITUDE] << ',' << m_values[TelemetryValue::VERT_SPEED] << ';';
    std::string valuesStr = valuesStream.str();

    // Send data
    int len = m_port->sendData(valuesStr.c_str(), valuesStr.length());

    return len == valuesStr.length();
  }
}
}
