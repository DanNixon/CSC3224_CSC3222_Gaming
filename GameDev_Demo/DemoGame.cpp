/**
 * @file
 * @author Dan Nixon
 */

#include "DemoGame.h"

#include <Shaders.h>

#include <Profiler.h>

#include "KJSSimulatorControls.h"
#include "KMSimulatorControls.h"
#include "control.h"

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;
using namespace Engine::Input;

/**
 * @brief Creates a new demonstration game instance.
 */
DemoGame::DemoGame()
    : Game("Engine Demo", std::make_pair(640, 480))
{
}

DemoGame::~DemoGame()
{
}

/**
 * @copydoc Game::gameStartup
 */
int DemoGame::gameStartup()
{
  m_sp = new ShaderProgram();
  m_sp->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
  m_sp->addShader(new FragmentShader("../resources/shader/frag_col.glsl"));
  m_sp->link();

  m_cube = new RenderableObject(
      "test_cube", Mesh::LoadASCIIMeshFile("../resources/cube.asciimesh"),
      m_sp);
  m_cube->setModelMatrix(Matrix4::Translation(Vector3(0.0, 0.0, -10.0)) *
                         Matrix4::Rotation(45, Vector3(0, 1, 0)) *
                         Matrix4::Rotation(45, Vector3(1, 0, 0)));

  m_child = new RenderableObject(
      "test_sphere", Mesh::LoadModelFile("../resources/sphere.stl", 0), m_sp);
  m_child->setModelMatrix(Matrix4::Translation(Vector3(-2.0, 0.0, 0.0)) *
                          Matrix4::Rotation(30, Vector3(1, 0, 0)));

  m_cube->addChild(*m_child);

  m_s = new Scene(
      m_cube, Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)),
      Matrix4::Perspective(1, 100, 1.33f, 45.0f));

  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  if (JoystickHandler::NumJoysticks() == 0)
  {
    std::cout << "Using mouse and keyboard" << std::endl;
    m_simControls = new KMSimulatorControls(this);
  }
  else
  {
    std::cout << "Using joystick and keyboard" << std::endl;
    m_simControls = new KJSSimulatorControls(this);
	if (!static_cast<KJSSimulatorControls *>(m_simControls)
		->joystick()
		->open(0))
	{
		std::cerr << "Could not open joystick" << std::endl;
		return 50;
	}
  }

  m_graphicsLoop = addTimedLoop(16.66f, "graphics");
  m_physicsLoop = addTimedLoop(8.33f, "physics");
  m_profileLoop = addTimedLoop(1000.0f, "profile");

  m_testLoop = addTimedLoop(1000.0f, "test");

  m_profiler = new Profiler(this);

  return 0;
}

/**
 * @copydoc Game::gameLoop
 */
void DemoGame::gameLoop(Uint8 id, float dtMilliSec)
{
  if (id == m_graphicsLoop)
  {
    m_s->update();
    m_s->render();
    swapBuffers();
  }
  else if (id == m_physicsLoop)
  {
    // TODO
  }
  else if (id == m_profileLoop)
  {
    m_profiler->computeStats(dtMilliSec);
    std::cout << "Performance statistics:" << std::endl
              << *m_profiler << std::endl;
  }
  else if (id == m_testLoop)
  {
    std::cout << "P: " << m_simControls->analog(A_PITCH) << std::endl
              << "R: " << m_simControls->analog(A_ROLL) << std::endl
              << "T: " << m_simControls->analog(A_THROT) << std::endl
              << "Y: " << m_simControls->analog(A_YAW) << std::endl
              << "FPV: " << m_simControls->state(S_FPV) << std::endl;
  }
}

/**
 * @copydoc Game::gameShutdown
 */
void DemoGame::gameShutdown()
{
}
