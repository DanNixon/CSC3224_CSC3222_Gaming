/**
 * @file
 * @author Dan Nixon
 */

#include <iostream>

#include "SnookerSimulation.h"
#include <Entity.h>

using namespace Engine::Maths;
using namespace Simulation::Physics;

int main(int argc, char *argv[])
{
  Simulation::Snooker::SnookerSimulation s;
  return s.run();
}
