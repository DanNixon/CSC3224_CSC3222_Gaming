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
#include "Profiler.h"

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
      , m_profiler(NULL)
  {
    for (Uint8 i = 0; i < MAX_TIMED_LOOPS; i++)
      m_loops[i] = NULL;

    QueryPerformanceFrequency(&m_freq);
  }

  Game::~Game()
  {
  }

  /**
   * @brief Run the game and process the main game loop.
   */
  int Game::run()
  {
    int status = init();

    if (status == 0)
    {
      this->gameLoadScreen();
      this->gameStartup();

      // Set time on loops
      QueryPerformanceCounter(&m_start);
      for (Uint8 i = 0; i < MAX_TIMED_LOOPS; i++)
      {
        if (m_loops[i] != NULL)
          m_loops[i]->lastFired = time();
      }

      SDL_Event e;
      bool exit = false;
      float startTime;
      while (!exit)
      {
        if (m_profiler)
          m_profiler->m_loopUpdates[Profiler::MAIN_LOOP]++;

        // Handle SDL events
        while (SDL_PollEvent(&e) == 1)
        {
          // Start event profiling
          if (m_profiler != NULL)
          {
            m_profiler->m_loopUpdates[Profiler::EVENTS]++;
            startTime = time();
          }

          // Handle quit
          if (e.type == SDL_QUIT)
          {
            exit = true;
            break;
          }

          // Dispatch event
          for (IEventHandler::HandlerListIter it = m_eventHandlers.begin();
               it != m_eventHandlers.end(); ++it)
            (*it)->handleEvent(e);

          // End event profiling
          if (m_profiler != NULL)
            m_profiler->m_duration[Profiler::EVENTS] += time() - startTime;
        }

        // Poll timed loops
        for (Uint8 i = 0; i < MAX_TIMED_LOOPS; i++)
        {
          if (m_loops[i] == NULL)
            continue;

          float t = time();
          float deltaT = t - m_loops[i]->lastFired;

          // If interval has elapsed
          if (deltaT >= m_loops[i]->interval)
          {
            // Start loop profiling
            if (m_profiler != NULL)
            {
              m_profiler->m_loopUpdates[i]++;
              startTime = time();
            }

            // Dispatch handler
            m_loops[i]->lastFired = t;
            this->gameLoop(i, deltaT);

            // End loop profiling
            if (m_profiler != NULL)
              m_profiler->m_duration[i] += time() - startTime;
          }
        }
      }

      this->gameShutdown();
    }

    return status;
  }

  float Game::time() const
  {
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return (float)((t.QuadPart - m_start.QuadPart) * 1000.0f / m_freq.QuadPart);
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
   * @brief Shows a loading screen between initialisation and first render.
   */
  void Game::gameLoadScreen()
  {
    // TODO
  }

  int Game::init()
  {
    int result = 0;

    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK) < 0)
    {
      std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError()
                << std::endl;
      result = 1;
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
        result = 2;
      }
      else
      {
        /* Create context */
        m_context = SDL_GL_CreateContext(m_window);
        if (m_context == NULL)
        {
          std::cerr << "OpenGL context could not be created! SDL Error: "
                    << SDL_GetError() << std::endl;
          result = 3;
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
            result = 4;
          }
        }
      }
    }

    return result;
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

  Uint8 Game::addTimedLoop(float interval, const std::string &name)
  {
    Uint8 idx = 0;
    while (m_loops[idx] != NULL && idx < MAX_TIMED_LOOPS)
      idx++;

    GameLoopConfiguration *config = new GameLoopConfiguration;

    config->interval = interval;
    config->loopName = name;
    config->lastFired = 0.0f;

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
