#pragma once

#include <Windows.h>

class Timer
{
public:
  static void Init();
  static float SystemTime(LARGE_INTEGER start);

private:  
  static LARGE_INTEGER s_freq;

public:
  Timer();
  ~Timer();

  void start();
  void stop();

  float absoluteTime() const;
  float timeSinceLastFrame() const;
  float frameTime();

private:
  bool m_running;
  LARGE_INTEGER m_start;
  float m_lastFrameTime;
};

