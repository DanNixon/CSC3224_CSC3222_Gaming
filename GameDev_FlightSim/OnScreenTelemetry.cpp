/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "OnScreenTelemetry.h"

#include <sstream>

using namespace Engine::Maths;

namespace GameDev
{
namespace FlightSim
{
  OnScreenTelemetry::OnScreenTelemetry(SceneObject *parent)
      : ITelemetryProtocol()
      , SceneObject("on_screen_telemetry", parent)
  {
    // Ensure all required values are present
    m_values[TelemetryValue::RSSI] = 0.0f;
    m_values[TelemetryValue::CURRENT] = 0.0f;
    m_values[TelemetryValue::VBAT] = 0.0f;
    m_values[TelemetryValue::ALTITUDE] = 0.0f;

    // RSSI indicator
    m_rssi = new TelemetryValueIndicator("rssi", this, "RSSI");
    m_rssi->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 3.75f, 0.0f)));

    // Battery voltage indicator
    m_batteryVolts = new TelemetryValueIndicator("battery_volts", this, "VOLTS");
    m_batteryVolts->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 1.25f, 0.0f)));
    m_batteryVolts->setAlarmLevels(10.5f, 9.9f);

    // Battery current indicator
    m_batteryCurrent = new TelemetryValueIndicator("batery_current", this, "AMPS");
    m_batteryCurrent->setModelMatrix(Matrix4::Translation(Vector3(0.0f, -1.25f, 0.0f)));

    // Altitude indicator
    m_altitude = new TelemetryValueIndicator("altitude", this, "ALTITUDE");
    m_altitude->setModelMatrix(Matrix4::Translation(Vector3(0.0f, -3.75f, 0.0f)));

    // Set initial values
    send();
  }

  OnScreenTelemetry::~OnScreenTelemetry()
  {
  }

  bool OnScreenTelemetry::send()
  {
    // Don't spend time changing the text if it is invisible
    if (!m_active)
      return false;

    m_rssi->setValue(m_values[TelemetryValue::RSSI]);
    m_batteryVolts->setValue(m_values[TelemetryValue::VBAT], 3);
    m_batteryCurrent->setValue(m_values[TelemetryValue::CURRENT], 3);
    m_altitude->setValue(m_values[TelemetryValue::ALTITUDE], 3);

    return true;
  }
}
}
