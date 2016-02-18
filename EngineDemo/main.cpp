/** @file */

#include "stdafx.h"

#include <string>

#include <Game.h>

#include "Scene.h"
#include "RenderableObject.h"
#include "Matrix3.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Shaders.h"

class DemoGame : public Game
{
public:
  DemoGame() : Game("Test 2", std::make_pair(640, 480)) {}

  void setup()
  {
    m_sp = new ShaderProgram();
    m_sp->addShader(new VertexShader("basic_vertex.glsl"));
    m_sp->addShader(new FragmentShader("basic_fragment.glsl"));
    m_sp->link();

    m_cube = new RenderableObject(Mesh::LoadASCIIMeshFile("cube.asciimesh"), m_sp);
    m_cube->setModelMatrix(Matrix4::Translation(Vector3(0.0, 0.0, -10.0)) *
                           Matrix4::Rotation(45, Vector3(0, 1, 0)) *
                           Matrix4::Rotation(45, Vector3(1, 0, 0)));

    m_child = new RenderableObject(Mesh::LoadModelFile("sphere.stl", 0), m_sp);
    m_child->setModelMatrix(Matrix4::Translation(Vector3(-2.0, 0.0, 0.0)) *
                            Matrix4::Rotation(30, Vector3(1, 0, 0)));

    m_cube->addChild(*m_child);

    m_s = new Scene(m_cube,
                    Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)),
                    Matrix4::Perspective(1, 100, 1.33f, 45.0f));

    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
  }

  void loop(unsigned long dtUs)
  {
    m_s->update();
    m_s->render();
  }

  void tearDown()
  {
  }

private:
  ShaderProgram * m_sp;
  RenderableObject * m_cube;
  RenderableObject * m_child;
  Scene * m_s;
};

int main(int argc, char *args[])
{
  DemoGame g;

  g.init();
  g.run();

  return 0;
}
