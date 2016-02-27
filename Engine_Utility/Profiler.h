/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <Game.h>

namespace Engine
{
namespace Utility
{
  class Profiler
  {
  public:
    Profiler(Engine::Common::Game * target);
    virtual ~Profiler();

  private:
    friend class Engine::Common::Game;

    void computeStats(Uint32 dtMilliSec);

    Engine::Common::Game * m_target;

    unsigned long m_loopUpdates[Engine::Common::Game::MAX_TIMED_LOOPS + 1];
    float m_rate[Engine::Common::Game::MAX_TIMED_LOOPS + 1];
  };
}
}