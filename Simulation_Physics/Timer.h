/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <Windows.h>

namespace Simulation
{
namespace Physics
{
  /**
   * @class Timer
   * @brief Provides timing of a game loop.
   * @author Dan Nixon
   */
  class Timer
  {
  public:
    static void Init();

  private:
    static LARGE_INTEGER s_freq; //!< Performance counter frequency

  public:
    Timer();
    ~Timer();

    void start();
    void stop();

    float absoluteTime() const;
    float timeSinceLastFrame() const;
    float frameTime();

  private:
    bool m_running;        //!< Flag to indicate if the timer is running
    LARGE_INTEGER m_start; //!< Time at which timer was started
    float m_lastFrameTime; //!< Time of last recorded update frame
  };
}
}
