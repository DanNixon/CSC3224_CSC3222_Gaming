#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

#include <stdio.h>
#include <string>

#include "RenderObject.h"
#include "Matrix3.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
void handleKeys(unsigned char key, int x, int y);
void update();
void render(const RenderObject &o);
void close();

SDL_Window* gWindow = NULL;
SDL_GLContext gContext;
Matrix4 viewMatrix = Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10));
Matrix4 projMatrix = Matrix4::Perspective(1, 100, 1.33f, 45.0f);

bool init()
{
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  }
  else
  {
    //Use OpenGL 3.1 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Create window
    gWindow = SDL_CreateWindow("Test",
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    }
    else
    {
      //Create context
      gContext = SDL_GL_CreateContext(gWindow);
      if (gContext == NULL)
      {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      }
      else
      {
        //Initialize GLEW
        glewExperimental = GL_TRUE;
        GLenum glewError = glewInit();
        if (glewError != GLEW_OK)
        {
          printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
        }
      }
    }
  }

  return success;
}

void handleKeys(unsigned char key, int x, int y)
{
}

void update()
{
}

void render(const RenderObject &o)
{
  Matrix4 modelMatrix = o.GetWorldTransform();

  if (o.GetShader() && o.GetMesh())
  {
    GLuint program = o.GetShader()->GetShaderProgram();

    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false, (float*)&modelMatrix);
    glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false, (float*)&viewMatrix);
    glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, false, (float*)&projMatrix);

    Matrix3 rotation = Matrix3(viewMatrix);
    Vector3 invCamPos = viewMatrix.GetPositionVector();
    Vector3 camPos = rotation * -invCamPos;
    glUniform3fv(glGetUniformLocation(program, "cameraPos"), 1, (float *)&camPos);

    glUniform1i(glGetUniformLocation(program, "objectTextures[0]"), 0);
    glUniform1i(glGetUniformLocation(program, "objectTextures[1]"), 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, o.GetTexture(0));
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, o.GetTexture(1));

    o.Draw();
  }

  for (vector<RenderObject *>::const_iterator i = o.GetChildren().begin();
  i != o.GetChildren().end(); ++i)
  {
    render(*(*i));
  }
}

void close()
{
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_Quit();
}

int main(int argc, char* args[])
{
  if (!init())
    printf("Failed to initialize!\n");
  else
  {
    bool quit = false;
    SDL_Event e;
    SDL_StartTextInput();

    Mesh *cubeMesh = Mesh::LoadMeshFile("cube.asciimesh");
    Shader *shader = new Shader("basic_vertex.glsl", "basic_fragment.glsl");
    RenderObject cube(cubeMesh, shader);
    cube.SetModelMatrix(Matrix4::Translation(Vector3(0.0, 0.0, -10.0)) * Matrix4::Rotation(45, Vector3(0, 1, 0)) * Matrix4::Rotation(45, Vector3(1, 0, 0)));

    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    while (!quit)
    {
      //Handle events on queue
      while (SDL_PollEvent(&e) != 0)
      {
        if (e.type == SDL_QUIT)
          quit = true;
      }

      cube.Update(0);
      render(cube);

      SDL_GL_SwapWindow(gWindow);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    SDL_StopTextInput();
  }

  close();
  return 0;
}