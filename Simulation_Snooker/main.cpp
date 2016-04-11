/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
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
