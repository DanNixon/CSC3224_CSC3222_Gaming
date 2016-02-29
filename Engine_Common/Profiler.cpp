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
    for (int i = 0; i < NUM_PROFILES; i++)
    {
      m_avgFrameRate[i] = ((float)m_loopUpdates[i] / (float)dtMilliSec) * 1000.0f;

      if (m_loopUpdates[i] > 0)
        m_avgDuration[i] = m_duration[i] / (float)m_loopUpdates[i];
      else
        m_avgDuration[i] = 0.0f;

      m_loopUpdates[i] = 0;
      m_duration[i] = 0;
    }
  }

  float Profiler::frameRate(int idx) const
  {
    return m_avgFrameRate[idx];
  }

  float Profiler::averageDuration(int idx) const
  {
    return m_avgDuration[idx];
  }

  void Profiler::detailRates(std::ostream &stream) const
  {
    for (int i = 0; i < NUM_PROFILES; i++)
    {
      if (i == MAIN_LOOP)
        stream << "Main loop";
      else if (i == EVENTS)
        stream << "Event handling";
      else if (m_target->m_loops[i])
        stream << m_target->m_loops[i]->loopName;
      else
        continue;

      stream << " " << m_avgFrameRate[i] << " FPS, average duration: " <<
        m_avgDuration[i] << "ms" << std::endl;
    }
  }
}
}