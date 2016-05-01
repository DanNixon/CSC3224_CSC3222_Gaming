/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_ONSCREENTELEMETRY_H_
#define _GAMEDEV_FLIGHTSIM_ONSCREENTELEMETRY_H_

#include "ITelemetryProtocol.h"

#include <Engine_Common/SceneObject.h>

#include "TelemetryValueIndicator.h"

namespace GameDev
{
namespace FlightSim
{
  /**
   * @class OnScreenTelemetry
   * @brief Provides on screen telemetry readouts.
   * @author Dan Nixon
   */
  class OnScreenTelemetry : public ITelemetryProtocol, public Engine::Common::SceneObject
  {
  public:
    OnScreenTelemetry(Engine::Common::SceneObject *parent);
    virtual ~OnScreenTelemetry();

    bool send();

  private:
    friend class FlightSimGame;

    TelemetryValueIndicator *m_rssi;
    TelemetryValueIndicator *m_batteryVolts;
    TelemetryValueIndicator *m_batteryCurrent;
    TelemetryValueIndicator *m_altitude;
  };
}
}

#endif
