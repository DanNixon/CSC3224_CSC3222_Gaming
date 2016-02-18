#include "Timer.h"

void Timer::Init()
{
  QueryPerformanceFrequency(&s_freq);
}

Timer::Timer()
    : m_running(false)
{
}

Timer::~Timer()
{
}

void Timer::start()
{
  m_running = true;
  QueryPerformanceCounter(&m_start);
}

void Timer::stop()
{
  m_running = false;
}

float Timer::absoluteTime() const
{
  LARGE_INTEGER t;
  QueryPerformanceCounter(&t);
  return (float)((t.QuadPart - m_start.QuadPart) * 1000.0f / s_freq.QuadPart);
}

float Timer::timeSinceLastFrame() const
{
  return absoluteTime() - m_lastFrameTime;
}

float Timer::frameTime()
{
  m_lastFrameTime = absoluteTime();
  return m_lastFrameTime;
}