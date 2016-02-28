/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include "Game.h"

namespace Engine
{
namespace Common
{
  class Profiler
  {
  public:
    static const int MAIN_LOOP = Game::MAX_TIMED_LOOPS;

    Profiler(Engine::Common::Game * target);
    virtual ~Profiler();

    void computeStats(Uint32 dtMilliSec);

    float rate(int idx) const;
    void detailRates(std::ostream &stream) const;

  private:
    friend class Engine::Common::Game;

    Engine::Common::Game * m_target;

    unsigned long m_loopUpdates[Game::MAX_TIMED_LOOPS + 1];
    float m_rate[Game::MAX_TIMED_LOOPS + 1];
  };
}
}