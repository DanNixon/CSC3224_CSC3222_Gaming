/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include <iostream>

#include "PathFinder.h"

/**
 * @brief Entry point of the graphical path finder.
 */
int main(int argc, char *argv[])
{
  Simulation::GraphicalPathFinder::PathFinder p;
  return p.run();
}
