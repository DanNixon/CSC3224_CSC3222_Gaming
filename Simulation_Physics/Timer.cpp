/**
 * @file
 * @author Dan Nixon
 */

#include "Timer.h"

/**
 * @brief Initialises the timer, must be called before an instance of Timer is
 *        created.
 */
void Timer::Init()
{
  QueryPerformanceFrequency(&s_freq);
}

/**
 * @brief Creates an instance of a stopped timer.
 */
Timer::Timer()
    : m_running(false)
{
}

Timer::~Timer()
{
}

/**
 * @brief Starts the timer.
 *
 * If timer is already running then it will be reset to zero.
 */
void Timer::start()
{
  m_running = true;
  QueryPerformanceCounter(&m_start);
}

/**
 * @brief Stops the timer.
 */
void Timer::stop()
{
  m_running = false;
}

/**
 * @brief Gets the time since the timer was started.
 * @return Time since start
 */
float Timer::absoluteTime() const
{
  LARGE_INTEGER t;
  QueryPerformanceCounter(&t);
  return (float)((t.QuadPart - m_start.QuadPart) * 1000.0f / s_freq.QuadPart);
}

/**
 * @brief Gets the time since the last call to frameTime.
 * @return Time since last frame
 * @see Timer::frameTime
 */
float Timer::timeSinceLastFrame() const
{
  return absoluteTime() - m_lastFrameTime;
}

/**
 * @brief Records a frame and returns the elapsed time since the last frame.
 * @return Time since last frame
 * @see Timer::timeSinceLastFrame
 */
float Timer::frameTime()
{
  float t = absoluteTime();
  float dt = t - m_lastFrameTime;
  m_lastFrameTime = absoluteTime();
  return dt;
}
