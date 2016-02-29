/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_COMMON_PROFILER_H_
#define _ENGINE_COMMON_PROFILER_H_

#include "Game.h"

namespace Engine
{
namespace Common
{
  class Profiler
  {
  public:
    static const int NUM_PROFILES = Game::MAX_TIMED_LOOPS + 2;

    static const int MAIN_LOOP = Game::MAX_TIMED_LOOPS;
    static const int EVENTS = Game::MAX_TIMED_LOOPS + 1;

    Profiler(Engine::Common::Game * target);
    virtual ~Profiler();

    void computeStats(float dtMilliSec);

    float frameRate(int idx) const;
    float averageDuration(int idx) const;

    void detailRates(std::ostream &stream) const;

  private:
    friend class Engine::Common::Game;

    Game * m_target;

    unsigned long m_loopUpdates[NUM_PROFILES];
    float m_duration[NUM_PROFILES];

    float m_avgDuration[NUM_PROFILES];
    float m_avgFrameRate[NUM_PROFILES];
  };
}
}

#endif