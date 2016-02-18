/** @file */

#include "stdafx.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

#include <stdio.h>
#include <string>

#include "Scene.h"
#include "RenderableObject.h"
#include "Matrix3.h"
#include "Mesh.h"
#include "Shader.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
void close();

SDL_Window *gWindow = NULL;
SDL_GLContext gContext;

bool init()
{
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  }
  else
  {
    // Use OpenGL 3.1 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    // Create window
    gWindow = SDL_CreateWindow(
        "Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
        SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    }
    else
    {
      // Create context
      gContext = SDL_GL_CreateContext(gWindow);
      if (gContext == NULL)
      {
        printf("OpenGL context could not be created! SDL Error: %s\n",
               SDL_GetError());
        success = false;
      }
      else
      {
        // Initialize GLEW
        glewExperimental = GL_TRUE;
        GLenum glewError = glewInit();
        if (glewError != GLEW_OK)
        {
          printf("Error initializing GLEW! %s\n",
                 glewGetErrorString(glewError));
        }
      }
    }
  }

  return success;
}

void close()
{
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_Quit();
}

int main(int argc, char *args[])
{
  if (!init())
    printf("Failed to initialize!\n");
  else
  {
    bool quit = false;
    SDL_Event e;
    SDL_StartTextInput();

    RenderableObject cube(Mesh::LoadASCIIMeshFile("cube.asciimesh"), new Shader("basic_vertex.glsl", "basic_fragment.glsl"));
    cube.setModelMatrix(Matrix4::Translation(Vector3(0.0, 0.0, -10.0)) *
                        Matrix4::Rotation(45, Vector3(0, 1, 0)) *
                        Matrix4::Rotation(45, Vector3(1, 0, 0)));

    RenderableObject cube2(Mesh::LoadModelFile("sphere.stl"), new Shader("basic_vertex.glsl", "basic_fragment.glsl"));
    cube2.setModelMatrix(Matrix4::Translation(Vector3(-2.0, 0.0, 0.0)) *
                         Matrix4::Rotation(30, Vector3(1, 0, 0)));

    cube.addChild(cube2);

    Scene s(&cube,
            Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)),
            Matrix4::Perspective(1, 100, 1.33f, 45.0f));

    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    while (!quit)
    {
      // Handle events on queue
      while (SDL_PollEvent(&e) != 0)
      {
        if (e.type == SDL_QUIT)
          quit = true;
      }

      s.update();
      s.render();

      SDL_GL_SwapWindow(gWindow);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    SDL_StopTextInput();
  }

  close();
  return 0;
}
