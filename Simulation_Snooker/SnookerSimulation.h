/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <Game.h>

/**
 * @class SnookerSimulation
 * @brief Game application for the snooker simulation.
 * @author Dan Nixon
 */
class SnookerSimulation : public Engine::Common::Game
{
public:
  SnookerSimulation();
  ~SnookerSimulation();

protected:
  void gameStartup();
  void gameLoop(unsigned long dtUs);
  void gameShutdown();
};
