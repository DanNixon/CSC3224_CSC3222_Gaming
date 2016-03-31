/**
 * @file
 * @author Dan Nixon
 */

#include <iostream>

#include "SnookerSimulation.h"

/**
 * @brief Entry point of the snooker simulation.
 */
int main(int argc, char *argv[])
{
  Simulation::Snooker::SnookerSimulation s;
  return s.run();
}
