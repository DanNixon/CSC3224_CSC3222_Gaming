/**
 * @file
 * @author Dan Nixon
 */

#include "Game.h"

#include <iostream>

#include <gl\glew.h>
#include <SDL\SDL_opengl.h>
#include <gl\glu.h>

#include "IEventHandler.h"

namespace Engine
{
namespace Common
{
  /**
   * @brief Creates a new game instance.
   * @param windowTitle Window title string
   * @param resolution Window resolution
   */
  Game::Game(std::string windowTitle, std::pair<int, int> resolution)
      : m_windowTitle(windowTitle)
      , m_windowWidth(resolution.first)
      , m_windowHeight(resolution.second)
  {
    for (Uint8 i = 0; i < MAX_TIMED_LOOPS; i++)
      m_loops[i] = NULL;
  }

  Game::~Game()
  {
  }

  /**
   * @brief Initializes the game engine.
   * @return True if engine is successfully initialised
   * @see Game::isInitialised
   */
  bool Game::init()
  {
    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK) < 0)
    {
      std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError()
                << std::endl;
      m_initialised = false;
    }
    else
    {
      /* Use OpenGL 3.1 core */
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                          SDL_GL_CONTEXT_PROFILE_CORE);

      /* Create window */
      m_window = SDL_CreateWindow(
          m_windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
          SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight,
          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

      if (m_window == NULL)
      {
        std::cerr << "Window could not be created! SDL Error: "
                  << SDL_GetError() << std::endl;
        m_initialised = false;
      }
      else
      {
        /* Create context */
        m_context = SDL_GL_CreateContext(m_window);
        if (m_context == NULL)
        {
          std::cerr << "OpenGL context could not be created! SDL Error: "
                    << SDL_GetError() << std::endl;
          m_initialised = false;
        }
        else
        {
          /* Initialize GLEW */
          glewExperimental = GL_TRUE;
          GLenum glewError = glewInit();
          if (glewError != GLEW_OK)
          {
            std::cerr << "Error initializing GLEW: "
                      << glewGetErrorString(glewError) << std::endl;
          }
        }
      }
    }

    m_initialised = true;
    return m_initialised;
  }

  /**
   * @brief Run the game and process the main game loop.
   */
  void Game::run()
  {
    if (!m_initialised)
      return;

    this->gameStartup();

    // Set time on loops
    for (Uint8 i = 0; i < MAX_TIMED_LOOPS; i++)
    {
      if (m_loops[i] != NULL)
        m_loops[i]->lastFired = SDL_GetTicks();
    }

    SDL_Event e;
    bool exit = false;
    while (!exit)
    {
      while (SDL_PollEvent(&e) == 1)
      {
        if (e.type == SDL_QUIT)
        {
          exit = true;
          break;
        }

        for (IEventHandler::HandlerListIter it = m_eventHandlers.begin();
             it != m_eventHandlers.end(); ++it)
          (*it)->handleEvent(e);
      }

      for (Uint8 i = 0; i < MAX_TIMED_LOOPS; i++)
      {
        if (m_loops[i] == NULL)
          continue;

        Uint32 t = SDL_GetTicks();
        Uint32 deltaT = t - m_loops[i]->lastFired;

        if (deltaT >= m_loops[i]->interval)
        {
          m_loops[i]->lastFired = t;
          this->gameLoop(i, deltaT);
        }
      }
    }

    this->gameShutdown();
  }

  /**
   * @brief Adds an event handler to be updated in the game loop.
   * @param handler Event hander to add
   */
  void Game::addEventHandler(IEventHandler *handler)
  {
    m_eventHandlers.push_back(handler);
  }

  /**
   * @brief Gets the window aspect ratio.
   * @return Aspect ratio
   */
  float Game::windowAspect() const
  {
    return ((float)m_windowHeight / (float)m_windowWidth);
  }

  void Game::swapBuffers()
  {
    SDL_GL_SwapWindow(m_window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  /**
  * @brief Shuts down the game engine.
  */
  void Game::close()
  {
    SDL_DestroyWindow(m_window);
    m_window = NULL;
    SDL_Quit();
  }

  Uint8 Game::addTimedLoop(Uint32 interval, const std::string &name)
  {
    Uint8 idx = 0;
    while (m_loops[idx] != NULL && idx < MAX_TIMED_LOOPS)
      idx++;

    GameLoopConfiguration *config = new GameLoopConfiguration;

    config->interval = interval;
    config->loopName = name;
    config->lastFired = 0;

    m_loops[idx] = config;

    return idx;
  }

  void Game::removeTimedLoop(Uint8 id)
  {
    if (m_loops[id] != NULL)
      delete m_loops[id];

    m_loops[id] = NULL;
  }
}
}
