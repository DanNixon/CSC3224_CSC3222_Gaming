/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <string>
#include <SDL.h>

/**
 * @class Game
 * @author Dan Nxion
 * @brief Contains setup and shutdown logic for the game engine, should be the
 *        base class of any game using the engine.
 */
class Game
{
public:
  Game(std::string WindowTitle, std::pair<int, int> resolution);
  virtual ~Game();

  bool init();
  void run();

  float windowAspect() const;

  /**
   * @brief Performs any setup specific to the game.
   */
  virtual void setup() = 0;

  /**
   * @brief The main game loop.
   * @param dtUs TIme since last loop in microseconds
   */
  virtual void loop(unsigned long dtUs) = 0;

  /**
   * @brief Performs any shutdown logic specific to the game.
   */
  virtual void tearDown() = 0;

private:
  void close();

  SDL_Window *m_window;    //!< SDL window
  SDL_GLContext m_context; //!< GL context

protected:
  std::string m_windowTitle; //!< Window title
  int m_windowWidth;         //!< Window width
  int m_windowHeight;        //!< Window height
};
