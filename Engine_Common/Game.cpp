/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "Game.h"

#include <sstream>

// clang-format off
#include <gl/glew.h>
#include <SDL/SDL_opengl.h>
#include <gl/glu.h>
#include <SDL_ttf.h>
#include <alut.h>
// clang-formmat on

#include <Engine_Logging/Logger.h>
#include <Engine_Logging/LoggingService.h>
#include <Engine_Logging/ConsoleOutputChannel.h>
#include <Engine_ResourceManagment/MemoryManager.h>

#include "Profiler.h"

#include "debug_utils.h"

using namespace Engine::Logging;

namespace
{
  Logger g_log(__FILE__);
}

namespace Engine
{
namespace Common
{
  /**
   * @brief Creates a new game instance.
   * @param name Name of the game (as displayed in window title)
   * @param resolution Window resolution
   */
  Game::Game(const std::string &name, std::pair<int, int> resolution)
      : m_name(name)
      , m_windowWidth(resolution.first)
      , m_windowHeight(resolution.second)
      , m_profiler(nullptr)
  {
    // Default logging configuration
    ConsoleOutputChannel * console = new ConsoleOutputChannel();
    console->setLevel(LogLevel::INFO);
    LoggingService::Instance().addOutput(console);

    for (Uint8 i = 0; i < MAX_TIMED_LOOPS; i++)
      m_loops[i] = nullptr;

    QueryPerformanceFrequency(&m_freq);

#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
  }

  Game::~Game()
  {
    for (Uint8 i = 0; i < MAX_TIMED_LOOPS; i++)
    {
      if (m_loops[i])
        delete m_loops[i];
    }

    if (m_profiler)
      delete m_profiler;
  }

  /**
   * @brief Run the game and process the main game loop.
   */
  int Game::run()
  {
    int status = init();

    g_log.info("Game run");

    if (status != 0)
      return status;

    this->gameLoadScreen();
    status = this->gameStartup();

    if (status != 0)
      return status;

    // Set time on loops
    QueryPerformanceCounter(&m_start);
    for (Uint8 i = 0; i < MAX_TIMED_LOOPS; i++)
    {
      if (m_loops[i] != nullptr)
        m_loops[i]->lastFired = time();
    }

    m_run = true;

    SDL_Event e;
    float startTime;
    while (m_run)
    {
      if (m_profiler)
        m_profiler->m_loopUpdates[Profiler::MAIN_LOOP]++;

      // Handle SDL events
      while (SDL_PollEvent(&e) == 1)
      {
        // Start event profiling
        if (m_profiler != nullptr)
        {
          m_profiler->m_loopUpdates[Profiler::EVENTS]++;
          startTime = time();
        }

        // Handle quit
        if (e.type == SDL_QUIT)
        {
          m_run = false;
          break;
        }

        // Dispatch event
        for (IEventHandler::HandlerListIter it = m_eventHandlers.begin();
             it != m_eventHandlers.end(); ++it)
          (*it)->handleEvent(e);

        // End event profiling
        if (m_profiler != nullptr)
          m_profiler->m_duration[Profiler::EVENTS] += time() - startTime;
      }

      // Poll timed loops
      for (Uint8 i = 0; i < MAX_TIMED_LOOPS; i++)
      {
        if (m_loops[i] == nullptr)
          continue;

        float t = time();
        float deltaT = t - m_loops[i]->lastFired;

        // If interval has elapsed
        if (deltaT >= m_loops[i]->interval)
        {
          // Start loop profiling
          if (m_profiler != nullptr)
          {
            m_profiler->m_loopUpdates[i]++;
            startTime = time();
          }

          // Dispatch handler
          m_loops[i]->lastFired = t;
          this->gameLoop(i, deltaT);

          // End loop profiling
          if (m_profiler != nullptr)
            m_profiler->m_duration[i] += time() - startTime;
        }
      }
    }

    this->gameShutdown();

    // Free ALL the memory
    MemoryManager::Instance().releaseAll();

    return status;
  }

  /**
   * @brief Stops the game loop executing and exits.
   */
  void Game::exit()
  {
    m_run = false;
  }

  /**
   * @brief Gets the time since startup in milliseconds.
   * @return Time in ms
   */
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
   * @brief Removes an event handler.
   * @param handler Event hander to remove
   */
  void Game::removeEventHandler(IEventHandler *handler)
  {
    auto it = std::find(m_eventHandlers.begin(), m_eventHandlers.end(), handler);
    if (it != m_eventHandlers.end())
      m_eventHandlers.erase(it);
  }

  /**
   * @brief Gets the window aspect ratio.
   * @return Aspect ratio
   */
  float Game::windowAspect() const
  {
    return ((float)m_windowWidth / (float)m_windowHeight);
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
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, -1.0f);

    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();

    swapBuffers();
  }

  int Game::init()
  {
    g_log.info("Game init");

    int result = 0;

    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK) < 0)
    {
      g_log.critical("SDL failed to initialize! SDL Error: " + std::string(SDL_GetError()));
      result = 1;
    }
    else
    {
      if (TTF_Init() < 0)
      {
        g_log.critical("TTF extension failed to initialize! Error: " + std::string(TTF_GetError()));
        result = 10;
      }

      if (!alutInitWithoutContext(0, nullptr))
      {
        g_log.critical("ALUT failed to initialize! Error: " + std::string(alutGetErrorString(alutGetError())));
        result = 11;
      }

      /* Use OpenGL 3.1 core */
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                          SDL_GL_CONTEXT_PROFILE_CORE);

      /* Create window */
      m_window = SDL_CreateWindow(
          m_name.c_str(), SDL_WINDOWPOS_UNDEFINED,
          SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight,
          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

      if (m_window == nullptr)
      {
        g_log.critical("Window could not be created! SDL Error: " + std::string(SDL_GetError()));
        result = 2;
      }
      else
      {
        /* Create context */
        m_context = SDL_GL_CreateContext(m_window);
        if (m_context == nullptr)
        {
          g_log.critical("OpenGL context could not be created! SDL Error: " + std::string(SDL_GetError()));
          result = 3;
        }
        else
        {
          /* Initialize GLEW */
          glewExperimental = GL_TRUE;
          GLenum glewError = glewInit();
          if (glewError != GLEW_OK)
          {
            std::stringstream str;
            str << glewGetErrorString(glewError);
            g_log.critical("Error initializing GLEW: " + str.str());
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
    m_window = nullptr;
    TTF_Quit();
    alutExit();
    SDL_Quit();
    LoggingService::Instance().shutdown();
  }

  Uint8 Game::addTimedLoop(float interval, const std::string &name)
  {
    Uint8 idx = 0;
    while (m_loops[idx] != nullptr && idx < MAX_TIMED_LOOPS)
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
    if (m_loops[id] != nullptr)
      delete m_loops[id];

    m_loops[id] = nullptr;
  }
}
}
