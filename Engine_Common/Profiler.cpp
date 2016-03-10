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
  /**
   * @brief Creates a new profiler for a given Game.
   * @param target Game to profile
   */
  Profiler::Profiler(Game *target)
      : m_target(target)
  {
  }

  Profiler::~Profiler()
  {
  }

  /**
   * @brief Compute statistics on accumulated data.
   * @param dtMilliSec Time since last call to computeStats (in milliseconds)
   */
  void Profiler::computeStats(float dtMilliSec)
  {
    for (int i = 0; i < NUM_PROFILES; i++)
    {
      m_avgFrameRate[i] = ((float)m_loopUpdates[i] / dtMilliSec) * 1000.0f;

      if (m_loopUpdates[i] > 0)
        m_avgDuration[i] = m_duration[i] / (float)m_loopUpdates[i];
      else
        m_avgDuration[i] = 0.0f;

      m_loopUpdates[i] = 0;
      m_duration[i] = 0;
    }
  }

  /**
   * @brief Gets the frame rate for a given profile.
   * @param idx Profile ID
   * @return Frame rate
   */
  float Profiler::frameRate(int idx) const
  {
    return m_avgFrameRate[idx];
  }

  /**
   * @brief Gets the average execution duration of a profiled loop.
   * @param idx Profile ID
   * @return Average execution duration (milliseconds)
   */
  float Profiler::averageDuration(int idx) const
  {
    return m_avgDuration[idx];
  }

  /**
   * @brief Outputs friendly formatted performance statistics to a stream.
   * @param o Stream
   */
  void Profiler::outputToStream(std::ostream &o) const
  {
    std::streamsize p = o.precision();
    o.precision(3);

    std::string quantity = "FPS";
    for (int i = 0; i < NUM_PROFILES; i++)
    {
      if (i == MAIN_LOOP)
      {
        o << "Main loop";
        quantity = "iterations";
      }
      else if (i == EVENTS)
      {
        o << "Event handling";
        quantity = "events";
      }
      else if (m_target->m_loops[i])
        o << "Loop \"" << m_target->m_loops[i]->loopName << "\"";
      else
        continue;

      o << ": " << m_avgFrameRate[i] << " " << quantity << ", average duration: " << m_avgDuration[i] << "ms"
        << std::endl;
    }

    o.precision(p);
  }
}
}
