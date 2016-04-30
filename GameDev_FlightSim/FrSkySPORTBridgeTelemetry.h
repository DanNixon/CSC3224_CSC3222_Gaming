/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_FRSKYSPORTBRIDGETELEMETRY_H_
#define _GAMEDEV_FLIGHTSIM_FRSKYSPORTBRIDGETELEMETRY_H_

#include "ITelemetryProtocol.h"

#include "SerialPort.h"

namespace GameDev
{
namespace FlightSim
{
  class FrSkySPORTBridgeTelemetry : public ITelemetryProtocol
  {
  public:
    FrSkySPORTBridgeTelemetry();
    virtual ~FrSkySPORTBridgeTelemetry();

    bool send();
  };
}
}

#endif
