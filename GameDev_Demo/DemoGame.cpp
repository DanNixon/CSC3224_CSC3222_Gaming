/**
 * @file
 * @author Dan Nixon
 */

#include "DemoGame.h"

#include <sstream>

#include <Engine_Audio/WAVSource.h>
#include <Engine_Common/MemoryManager.h>
#include <Engine_Common/Profiler.h>
#include <Engine_Graphics/GraphicalScene.h>
#include <Engine_Graphics/ModelLoader.h>
#include <Engine_Graphics/PlaneMesh.h>
#include <Engine_Graphics/RectangleMesh.h>
#include <Engine_Graphics/Shaders.h>
#include <Engine_Maths/Quaternion.h>
#include <Engine_Physics/ConvexHullShape.h>
#include <Engine_Physics/StaticPlaneRigidBody.h>

#include "KJSSimulatorControls.h"
#include "KMSimulatorControls.h"
#include "OptionsMenu.h"
#include "control.h"

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;
using namespace Engine::Input;
using namespace Engine::Audio;
using namespace Engine::UIMenu;
using namespace Engine::Physics;

namespace GameDev
{
namespace Demo
{
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
    glClearColor(0.0f, 0.3f, 0.5f, 1.0f);

    // Menu
    m_font = TTF_OpenFont("../resources/open-sans/OpenSans-Regular.ttf", 20);
    m_menu = new OptionsMenu(this, m_font);

    m_menu->addNewItem(NULL, "exit", "Exit");
    m_menu->addNewItem(NULL, "pause", "Pause");

    MenuItem *aircraft = m_menu->addNewItem(NULL, "aircraft", "Aircraft");
    m_menu->addNewItem(aircraft, "Gaui X5");
    m_menu->addNewItem(aircraft, "Logo 600");

    MenuItem *terrain = m_menu->addNewItem(NULL, "terrain", "Terrain");
    m_menu->addNewItem(terrain, "Flat");
    m_menu->addNewItem(terrain, "Tall Peaks");
    m_menu->addNewItem(terrain, "Forest");

    m_menu->layout();
    m_menu->hide();
    addEventHandler(m_menu);

    // Shaders
    m_sp = new ShaderProgram();
    m_sp->addShader(new VertexShader("../resources/shader/vert_lighting.glsl"));
    m_sp->addShader(new FragmentShader("../resources/shader/frag_lighting.glsl"));
    m_sp->link();

    float initialModelDistance = 250.0f;

    // Scene
    m_losPMatrix = Matrix4::Perspective(1.0f, 1000000.0f, windowAspect(), 45.0f);
    m_fpvPMatrix = Matrix4::Perspective(10.0f, 1000000.0f, windowAspect(), 110.0f);
    m_s = new GraphicalScene(new SceneObject("root"),
                             Matrix4::BuildViewMatrix(Vector3(0, 50, 0), Vector3(0, 0, -initialModelDistance)),
                             m_losPMatrix);

    const std::string modelName("Gaui_X7");
    std::stringstream modelObjStr;
    modelObjStr << "../resources/models/" << modelName << "/" << modelName << ".obj";

    // Model
    ModelLoader l;
    m_model = l.load(modelObjStr.str(), m_sp);
    m_s->root()->addChild(m_model);

    // UI
    m_uiShader = new ShaderProgram();
    m_uiShader->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
    m_uiShader->addShader(new FragmentShader("../resources/shader/frag_col.glsl"));
    m_uiShader->link();

    m_ui = new GraphicalScene(new SceneObject("root"), Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -1)),
                              Matrix4::Orthographic(0.0f, -1.0f, 10.0f, -10.0f, 10.0f, -10.0f));

    RenderableObject *leftStickArea =
        new RenderableObject("left_stick_area", new RectangleMesh(Vector2(2.0f, 2.0f)), m_uiShader);
    leftStickArea->setModelMatrix(Matrix4::Translation(Vector3(-8.5f, -8.5f, 0.9f)));
    leftStickArea->mesh()->setStaticColour(Colour(0.5f, 0.5, 0.5f, 0.5f));
    m_ui->root()->addChild(leftStickArea);

    m_leftStick = new RenderableObject("left_stick", Mesh::GenerateDisc2D(0.2f), m_uiShader, NULL, true);
    m_leftStick->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.0f, -0.1f)));
    m_leftStick->mesh()->setStaticColour(Colour(1.0f, 0.0f, 0.0f, 0.8f));
    leftStickArea->addChild(m_leftStick);

    RenderableObject *rightStickArea =
        new RenderableObject("right_stick_area", new RectangleMesh(Vector2(2.0f, 2.0f)), m_uiShader);
    rightStickArea->setModelMatrix(Matrix4::Translation(Vector3(8.5f, -8.5f, 0.9f)));
    rightStickArea->mesh()->setStaticColour(Colour(0.5f, 0.5, 0.5f, 0.5f));
    m_ui->root()->addChild(rightStickArea);

    m_rightStick = new RenderableObject("right_stick", Mesh::GenerateDisc2D(0.2f), m_uiShader, NULL, true);
    m_rightStick->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.0f, -0.1f)));
    m_rightStick->mesh()->setStaticColour(Colour(1.0f, 0.0f, 0.0f, 0.8f));
    rightStickArea->addChild(m_rightStick);

    // Physics
    m_physicalSystem = new PhysicalSystem();

    RenderableObject *ground = new RenderableObject("ground", new PlaneMesh('y', 1000.0f), m_uiShader);
    ground->mesh()->setStaticColour(Colour(0.8f, 0.6f, 0.5f));
    SceneObjectMotionState *groundMotionState =
        new SceneObjectMotionState(ground, Vector3(0.0f, 0.0f, 0.0f), Quaternion());
    RigidBody *groundBody =
        new StaticPlaneRigidBody(groundMotionState, 0, btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 1.0f, 0.0f));
    m_physicalSystem->addBody(groundBody);
    m_s->root()->addChild(ground);

    SceneObjectMotionState *modelMotionState =
        new SceneObjectMotionState(m_model, Vector3(0.0f, 0.0f, -initialModelDistance), Quaternion(90.0f, 0.0f, 0.0f));
    ConvexHullShape *modelShape = new ConvexHullShape();
    modelShape->addSceneTreePoints(m_model);
    m_modelBody = new RigidBody(modelMotionState, 500000.0f, btVector3(0.0f, 0.0f, 0.0f), modelShape);
    m_modelBody->body()->setActivationState(DISABLE_DEACTIVATION);
    m_physicalSystem->addBody(m_modelBody);

    // Audio
    m_audioContext = new Context();
    m_audioContext->open();

    m_audioListener = new Listener("test_audio_listener");
    m_s->root()->addChild(m_audioListener);

    m_audioSource1 = new WAVSource("test_audio_source_1", m_audioListener);
    static_cast<WAVSource *>(m_audioSource1)->load("../resources/models/Gaui_R5/Gaui_R5.wav");
    m_audioSource1->setLooping(true);
    m_s->root()->addChild(m_audioSource1);

    m_audioSource2 = new WAVSource("test_audio_source_2", m_audioListener);
    static_cast<WAVSource *>(m_audioSource2)->load("../resources/models/Gaui_R5/blade.wav");
    m_audioSource2->setLooping(true);
    m_s->root()->addChild(m_audioSource2);

    // GL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
      m_simControls->setAnalogDeadbands(0.05f);
      if (!static_cast<KJSSimulatorControls *>(m_simControls)->joystick()->open(0))
      {
        std::cerr << "Could not open joystick" << std::endl;
        return 50;
      }
    }

    // Timed loops
    m_graphicsLoop = addTimedLoop(16.66f, "graphics");
    m_physicsLoop = addTimedLoop(8.33f, "physics");
    m_audioLoop = addTimedLoop(16.66f, "audio");
    m_profileLoop = addTimedLoop(1000.0f, "profile");

    m_testLoop = addTimedLoop(5000.0f, "test");

    // Profiling
    m_profiler = new Profiler(this);

    m_audioSource1->play();

    return 0;
  }

  /**
   * @copydoc Game::gameLoop
   */
  void DemoGame::gameLoop(Uint8 id, float dtMilliSec)
  {
    if (id == m_graphicsLoop)
    {
      // Show menu if required
      if (m_simControls->state(S_OPENMENU))
      {
        m_menu->visible() ? m_menu->hide() : m_menu->show();
        m_simControls->setState(S_OPENMENU, false);
      }

      // Blade sound when throttle is high
      if (abs(m_simControls->analog(A_THROT)) > 0.2 && !m_audioSource2->isPlaying())
        m_audioSource2->play();
      else if (abs(m_simControls->analog(A_THROT)) < 0.2 && m_audioSource2->isPlaying())
        m_audioSource2->stop();

      // Stick indicators
      m_leftStick->setModelMatrix(
          Matrix4::Translation(Vector3(m_simControls->analog(A_YAW), m_simControls->analog(A_THROT), -0.1f)));
      m_rightStick->setModelMatrix(
          Matrix4::Translation(Vector3(m_simControls->analog(A_ROLL), m_simControls->analog(A_PITCH), -0.1f)));

      // Look at aircraft
      // m_s->setViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 50, 0), m_model->modelMatrix().positionVector()));

      // Graphics update
      m_s->update(dtMilliSec, Subsystem::GRAPHICS);
      m_ui->update(dtMilliSec, Subsystem::GRAPHICS);
      m_menu->update(dtMilliSec, Subsystem::GRAPHICS);

      swapBuffers();
    }
    else if (id == m_physicsLoop)
    {
      // Model controls
      float yawRate = 0.1f;
      float prRate = 0.1f;
      float throtRate = 100000000.0f;

      float roll = m_simControls->analog(A_ROLL) * prRate;
      float pitch = -m_simControls->analog(A_PITCH) * prRate;
      float yaw = -m_simControls->analog(A_YAW) * yawRate;
      float throt = m_simControls->analog(A_THROT) * throtRate;

      // Orientation
      btTransform t = m_modelBody->body()->getWorldTransform();
      btQuaternion angularOffset;
      angularOffset.setEuler(yaw, roll, pitch);
      btQuaternion angle = t.getRotation() * angularOffset;
      t.setRotation(angle);

      // Thrust
      btVector3 rotorThrust(0.0f, throt, 0.0f);
      // TODO: rotate thrust vector

      m_modelBody->body()->setWorldTransform(t);
      m_modelBody->body()->applyCentralForce(rotorThrust);

      // Physics update
      m_physicalSystem->update(dtMilliSec);
    }
    else if (id == m_audioLoop)
    {
      // Audio update
      m_s->update(dtMilliSec, Subsystem::AUDIO);
    }
    else if (id == m_profileLoop)
    {
      m_profiler->computeStats(dtMilliSec);
      std::cout << "Performance statistics:" << std::endl << *m_profiler << std::endl;
    }
    else if (id == m_testLoop)
    {
      std::cout << "TEST LOOP" << std::endl;

      MenuItem *a = static_cast<MenuItem *>(m_menu->root()->findChild("pause"));
      a->setText("Resume");
      m_menu->layout();
    }
  }

  /**
   * @copydoc Game::gameShutdown
   */
  void DemoGame::gameShutdown()
  {
    m_audioContext->close();
  }
}
}