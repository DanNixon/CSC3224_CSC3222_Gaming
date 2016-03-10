/**
 * @file
 * @author Dan Nixon
 */

#include "DemoGame.h"

#include <MemoryManager.h>
#include <ModelLoader.h>
#include <Profiler.h>
#include <RectangleMesh.h>
#include <Shaders.h>

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
  // Scene
  m_sp = new ShaderProgram();
  m_sp->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
  m_sp->addShader(new FragmentShader("../resources/shader/frag_col.glsl"));
  m_sp->link();

  ModelLoader l;
  m_model = l.load("../resources/models/Gaui_R5/Gaui_R5.obj", m_sp);

  m_model->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.0f, -25.0f)) *
                          Matrix4::Rotation(90.0f, Vector3(0.0f, 1.0f, 0.0f)));

  m_losPMatrix = Matrix4::Perspective(1.0f, 1000000.0f, windowAspect(), 45.0f);
  m_fpvPMatrix = Matrix4::Perspective(10.0f, 1000000.0f, windowAspect(), 110.0f);
  m_s = new Scene(m_model, Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -1000)), m_losPMatrix);

  // UI
  m_uiShader = new ShaderProgram();
  m_uiShader->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
  m_uiShader->addShader(new FragmentShader("../resources/shader/frag_col.glsl"));
  m_uiShader->link();

  m_ui = new Scene(new SceneObject("root"), Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -1000)),
                   Matrix4::Orthographic(0.0f, -1.0f, 10.0f, -10.0f, 10.0f, -10.0f));

  RenderableObject *leftStickArea =
      new RenderableObject("left_stick_area", new RectangleMesh(Vector2(2.0f, 2.0f)), m_uiShader);
  leftStickArea->setModelMatrix(Matrix4::Translation(Vector3(-8.5f, -8.5f, 0.0f)));
  leftStickArea->mesh()->setStaticColour(Colour(0.5f, 0.5, 0.5f, 0.5f));
  m_ui->root()->addChild(*leftStickArea);

  m_leftStick = new RenderableObject("left_stick", Mesh::GenerateDisc2D(0.2f), m_uiShader);
  m_leftStick->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.0f, 0.1f)));
  m_leftStick->mesh()->setStaticColour(Colour(1.0f, 0.0f, 0.0f, 0.8f));
  leftStickArea->addChild(*m_leftStick);

  RenderableObject *rightStickArea =
      new RenderableObject("right_stick_area", new RectangleMesh(Vector2(2.0f, 2.0f)), m_uiShader);
  rightStickArea->setModelMatrix(Matrix4::Translation(Vector3(8.5f, -8.5f, 0.0f)));
  rightStickArea->mesh()->setStaticColour(Colour(0.5f, 0.5, 0.5f, 0.5f));
  m_ui->root()->addChild(*rightStickArea);

  m_rightStick = new RenderableObject("right_stick", Mesh::GenerateDisc2D(0.2f), m_uiShader);
  m_rightStick->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.0f, 0.1f)));
  m_rightStick->mesh()->setStaticColour(Colour(1.0f, 0.0f, 0.0f, 0.8f));
  rightStickArea->addChild(*m_rightStick);

  // GL
  // glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  // Input
  if (JoystickHandler::NumJoysticks() == 0)
  {
    std::cout << "Using mouse and keyboard" << std::endl;
    m_simControls = new KMSimulatorControls(this);
    m_simControls->setAnalogDeadbands(0.05f);
  }
  else
  {
    std::cout << "Using joystick and keyboard" << std::endl;
    m_simControls = new KJSSimulatorControls(this);
    m_simControls->setAnalogDeadbands(0.02f);
    if (!static_cast<KJSSimulatorControls *>(m_simControls)->joystick()->open(0))
    {
      std::cerr << "Could not open joystick" << std::endl;
      return 50;
    }
  }

  // Timed loops
  m_graphicsLoop = addTimedLoop(16.66f, "graphics");
  m_physicsLoop = addTimedLoop(8.33f, "physics");
  m_profileLoop = addTimedLoop(1000.0f, "profile");

  m_testLoop = addTimedLoop(1000.0f, "test");

  // Profiling
  m_profiler = new Profiler(this);

  std::cout << "Num allocations: " << MemoryManager::Instance().numAllocations() << std::endl;

  return 0;
}

/**
 * @copydoc Game::gameLoop
 */
void DemoGame::gameLoop(Uint8 id, float dtMilliSec)
{
  if (id == m_graphicsLoop)
  {
    float yawRate = 12.0f;
    float prRate = 10.0f;

    m_leftStick->setModelMatrix(
        Matrix4::Translation(Vector3(m_simControls->analog(A_YAW), m_simControls->analog(A_THROT), 0.1f)));
    m_rightStick->setModelMatrix(
        Matrix4::Translation(Vector3(m_simControls->analog(A_ROLL), m_simControls->analog(A_PITCH), 0.1f)));

    float roll = m_simControls->analog(A_ROLL) * prRate;
    float pitch = -m_simControls->analog(A_PITCH) * prRate;
    float yaw = -m_simControls->analog(A_YAW) * yawRate;

    m_model->setModelMatrix(m_model->modelMatrix() * Matrix4::Rotation(roll, Vector3(1.0f, 0.0f, 0.0f)) *
                            Matrix4::Rotation(pitch, Vector3(0.0f, 0.0f, 1.0f)) *
                            Matrix4::Rotation(yaw, Vector3(0.0f, 1.0f, 0.0f)));

    m_s->update();
    m_s->render();

    m_ui->update();
    m_ui->render();

    swapBuffers();
  }
  else if (id == m_physicsLoop)
  {
    // TODO
  }
  else if (id == m_profileLoop)
  {
    m_profiler->computeStats(dtMilliSec);
    std::cout << "Performance statistics:" << std::endl << *m_profiler << std::endl;
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
  std::cout << "Num allocations: " << MemoryManager::Instance().numAllocations() << std::endl;
}
