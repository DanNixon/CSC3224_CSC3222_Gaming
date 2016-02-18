/** @file */

#pragma once

#include <string>
#include <SDL.h>

class Game
{
public:
  Game(std::string WindowTitle, std::pair<int, int> resolution);
  virtual ~Game();

  bool init();
  void run();

  float windowAspect() const;

  virtual void setup() = 0;
  virtual void loop(unsigned long dtUs) = 0;
  virtual void tearDown() = 0;

private:
  void close();

  SDL_Window *m_window;
  SDL_GLContext m_context;

protected:
  std::string m_windowTitle;
  int m_windowWidth;
  int m_windowHeight;
};
