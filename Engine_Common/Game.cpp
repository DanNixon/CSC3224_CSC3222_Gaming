/**
 * @file
 * @author Dan Nixon
 */

#include "Game.h"

#include <iostream>

#include <gl\glew.h>
#include <SDL_opengl.h>
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
  }

  Game::~Game()
  {
  }

  /**
   * @brief Initializes the game engine.
   * @return True if engine is succesfully initialised
   */
  bool Game::init()
  {
    bool success = true;

    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError()
                << std::endl;
      success = false;
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
          "Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
          m_windowWidth, m_windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

      if (m_window == NULL)
      {
        std::cerr << "Window could not be created! SDL Error: "
                  << SDL_GetError() << std::endl;
        success = false;
      }
      else
      {
        /* Create context */
        m_context = SDL_GL_CreateContext(m_window);
        if (m_context == NULL)
        {
          std::cerr << "OpenGL context could not be created! SDL Error: "
                    << SDL_GetError() << std::endl;
          success = false;
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

    return success;
  }

  /**
   * @brief Run the game and process the main game loop.
   */
  void Game::run()
  {
    this->gameStartup();

    SDL_Event e;
    bool exit = false;
    while (!exit)
    {
      while (SDL_PollEvent(&e) != 0)
      {
        if (e.type == SDL_QUIT)
          exit = true;

        for (IEventHandler::HandlerListIter it = m_eventHandlers.begin(); it != m_eventHandlers.end(); ++it)
          (*it)->handleEvent(e);
      }

      this->gameLoop(0);

      SDL_GL_SwapWindow(m_window);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    this->gameShutdown();
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

  void Game::addEventHandler(IEventHandler * handler)
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
}
}
