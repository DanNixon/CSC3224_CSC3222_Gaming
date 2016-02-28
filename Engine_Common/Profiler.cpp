/**
 * @file
 * @author Dan Nixon
 */

#include "Profiler.h"
#include <iostream>

namespace Engine
{
namespace Common
{
  Profiler::Profiler(Game * target)
    : m_target(target)
  {
  }

  Profiler::~Profiler()
  {
  }

  void Profiler::computeStats(Uint32 dtMilliSec)
  {
    for (int i = 0; i < Game::MAX_TIMED_LOOPS + 1; i++)
    {
      m_rate[i] = ((float) m_loopUpdates[i] / (float) dtMilliSec) * 1000.0f;
      m_loopUpdates[i] = 0;
    }
  }

  float Profiler::rate(int idx) const
  {
    return m_rate[idx];
  }

  void Profiler::detailRates(std::ostream &stream) const
  {
    for (int i = 0; i < Game::MAX_TIMED_LOOPS + 1; i++)
    {
      if (i == MAIN_LOOP)
        stream << "Main loop";
      else if (m_target->m_loops[i])
        stream << m_target->m_loops[i]->loopName;
      else
        continue;

      stream << " " << m_rate[i] << " FPS" << std::endl;
    }
  }
}
}