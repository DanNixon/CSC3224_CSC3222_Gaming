#pragma once

#include <Game.h>

class SnookerSimulation : public Game
{
public:
  SnookerSimulation();
  ~SnookerSimulation();

protected:
  void gameStartup();
  void gameLoop(unsigned long dtUs);
  void gameShutdown();
};

