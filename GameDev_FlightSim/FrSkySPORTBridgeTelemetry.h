/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_FRSKYSPORTBRIDGETELEMETRY_H_
#define _GAMEDEV_FLIGHTSIM_FRSKYSPORTBRIDGETELEMETRY_H_

#include "ITelemetryProtocol.h"

#include <Engine_ResourceManagment\IMemoryManaged.h>

#include "SerialPort.h"

namespace GameDev
{
namespace FlightSim
{
  class FrSkySPORTBridgeTelemetry : public ITelemetryProtocol, public Engine::ResourceManagment::IMemoryManaged
  {
  public:
    FrSkySPORTBridgeTelemetry(SerialPort *port);
    virtual ~FrSkySPORTBridgeTelemetry();

    bool send();

  private:
    SerialPort *m_port;
  };
}
}

#endif
