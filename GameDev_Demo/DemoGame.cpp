/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "DemoGame.h"

#include <sstream>

#include <Engine_Audio/WAVSource.h>
#include <Engine_Common/Profiler.h>
#include <Engine_Graphics/GraphicalScene.h>
#include <Engine_Graphics/HeightmapMesh.h>
#include <Engine_Graphics/ModelLoader.h>
#include <Engine_Graphics/RectangleMesh.h>
#include <Engine_Graphics/Shaders.h>
#include <Engine_Graphics/SphericalMesh.h>
#include <Engine_IO/KVNode.h>
#include <Engine_Logging/FileOutputChannel.h>
#include <Engine_Logging/Logger.h>
#include <Engine_Maths/Quaternion.h>
#include <Engine_Physics/BoundingBoxShape.h>
#include <Engine_Physics/ConvexHullShape.h>
#include <Engine_Physics/StaticPlaneRigidBody.h>
#include <Engine_ResourceManagment/MemoryManager.h>

#include "KJSSimulatorControls.h"
#include "KMSimulatorControls.h"
#include "control.h"

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;
using namespace Engine::Input;
using namespace Engine::Audio;
using namespace Engine::UIMenu;
using namespace Engine::Physics;
using namespace Engine::IO;
using namespace Engine::Logging;

namespace
{
Logger g_log(__FILE__);
}

namespace GameDev
{
namespace Demo
{
  /**
   * @brief Creates a new demonstration game instance.
   */
  DemoGame::DemoGame()
      : ConfigurableGame("Engine Demo", std::make_pair(1024, 768))
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
    int retVal = ConfigurableGame::gameStartup();

    // Open file logger
    FileOutputChannel *fileLog = new FileOutputChannel(gameSaveDirectory() + "DemoGameLog.log");
    fileLog->open();
    LoggingService::Instance().addOutput(fileLog);

    // TODO: display dismissible on screen scontrols
    if (isFirstRun())
    {
      g_log.info("This is the first time the game has been launched.");
    }

    // Load fonts
    TTFFontLookup::Instance().add("main_font", TTF_OpenFont("../resources/open-sans/OpenSans-Regular.ttf", 20));

    // Load shaders
    ShaderProgram *aircraftShader = new ShaderProgram();
    aircraftShader->addShader(new VertexShader("../resources/shader/vert_lighting.glsl"));
    aircraftShader->addShader(new FragmentShader("../resources/shader/frag_lighting.glsl"));
    aircraftShader->link();
    ShaderProgramLookup::Instance().add("aircraft_shader", aircraftShader);

    ShaderProgram *uiShader = new ShaderProgram();
    uiShader->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
    uiShader->addShader(new FragmentShader("../resources/shader/frag_col.glsl"));
    uiShader->link();
    ShaderProgramLookup::Instance().add("ui_shader", uiShader);

    // Menu
    m_menu = new OptionsMenu(this, TTFFontLookup::Instance().get("main_font"));
    m_menu->populateAircraftMenu({{"Gaui X5", "gaui_x5"}, {"Logo 600", "logo_600"}});
    m_menu->populateTerrainMenu({{"Flat", "flat"}, {"Tall Peaks", "peaks"}, {"Forest", "forest"}});
    m_menu->layout();
    m_menu->hide();
    addEventHandler(m_menu);

    // UI
    m_ui = new GraphicalScene(new SceneObject("root"), Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -1)),
                              Matrix4::Orthographic(0.0f, -1.0f, 10.0f, -10.0f, 10.0f, -10.0f));
    m_leftStickIndicator = new StickIndicator("left_stick", m_ui->root());
    m_leftStickIndicator->setModelMatrix(Matrix4::Translation(Vector3(-8.5f, -8.5f, 0.9f)));
    m_rightStickIndicator = new StickIndicator("right_stick", m_ui->root());
    m_rightStickIndicator->setModelMatrix(Matrix4::Translation(Vector3(8.5f, -8.5f, 0.9f)));

    // Scene
    float initialModelDistance = 250.0f;

    m_losPMatrix = Matrix4::Perspective(1.0f, 1000000.0f, windowAspect(), 45.0f);
    m_fpvPMatrix = Matrix4::Perspective(10.0f, 1000000.0f, windowAspect(), 110.0f);
    m_s = new GraphicalScene(
        new SceneObject("root"),
        Matrix4::BuildViewMatrix(Vector3(0.0f, 250.0f, 0.0f), Vector3(0.0f, 0.0f, -initialModelDistance)),
        m_losPMatrix);

    // Audio
    m_audioContext = new Context();
    m_audioContext->open();
    m_audioListener = new Listener("audio_listener");
    m_s->root()->addChild(m_audioListener);

    // Physics
    m_physicalSystem = new PhysicalSystem(8.33f, 83.33f); // At best 120Hz, at worst 12Hz
    m_physicsDebugDraw = new DebugDrawEngine(ShaderProgramLookup::Instance().get("aircraft_shader"));
    m_physicsDebugDraw->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    m_physicalSystem->world()->setDebugDrawer(m_physicsDebugDraw);
    m_s->root()->addChild(m_physicsDebugDraw);

    // Model
    m_aircraft = new Aircraft("Gaui_X7");
    m_aircraft->loadMeshes();
    m_aircraft->loadAudio(m_audioListener);
    m_aircraft->initPhysics(m_physicalSystem, Vector3(0.0f, 50.0f, -initialModelDistance),
                            Quaternion(135.0f, 0.0f, 0.0f));
    m_s->root()->addChild(m_aircraft);
    m_aircraft->setThrust(3000.0f);
    m_aircraft->setAxisRates(Vector3(10.0f, 10.0f, 15.0f));

    // Ground
    HeightmapMesh *hm = new HeightmapMesh(1000, 1000, 100000.0f, 100000.0f); // 1 km^2
    hm->setHeight(50, 40, 10, true);
    RenderableObject *ground = new RenderableObject("ground", hm, ShaderProgramLookup::Instance().get("ui_shader"));
    ground->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.0f, -250.0f)));
    SceneObjectMotionState *groundMotionState =
        new SceneObjectMotionState(ground, Vector3(0.0f, 0.0f, 0.0f), Quaternion());
    RigidBody *groundBody =
        new StaticPlaneRigidBody(groundMotionState, 0, btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 1.0f, 0.0f));
    m_physicalSystem->addBody(groundBody);
    m_s->root()->addChild(ground);

    // GL setup
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.3f, 0.5f, 1.0f);

    // Input
    if (JoystickHandler::NumJoysticks() == 0)
    {
      g_log.info("Using mouse and keyboard");
      m_simControls = new KMSimulatorControls(this);
      m_simControls->setAnalogDeadbands(0.05f);
    }
    else
    {
      g_log.info("Using joystick and keyboard");
      m_simControls = new KJSSimulatorControls(this);
      m_simControls->setAnalogDeadbands(0.05f);
      if (!static_cast<KJSSimulatorControls *>(m_simControls)->joystick()->open(0))
      {
        g_log.error("Could not open joystick");
        return 50;
      }
    }

    // Timed loops
    m_graphicsLoop = addTimedLoop(16.66f, "graphics");
    m_physicsLoop = addTimedLoop(8.33f, "physics");
    m_audioLoop = addTimedLoop(16.66f, "audio");
    m_profileLoop = addTimedLoop(1000.0f, "profile");

    // Profiling
    m_profiler = new Profiler(this);

    return retVal;
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

      // Stick indicators
      m_leftStickIndicator->setStickPosition(m_simControls->analog(A_YAW), m_simControls->analog(A_THROT));
      m_rightStickIndicator->setStickPosition(m_simControls->analog(A_ROLL), m_simControls->analog(A_PITCH));

      // Look at aircraft
      m_s->setViewMatrix(
          Matrix4::BuildViewMatrix(Vector3(0.0f, 50.0f, 0.0f), m_aircraft->modelMatrix().positionVector()));

      // Graphics update
      m_physicalSystem->world()->debugDrawWorld();
      m_s->update(dtMilliSec, Subsystem::GRAPHICS);
      m_ui->update(dtMilliSec, Subsystem::GRAPHICS);
      m_menu->update(dtMilliSec, Subsystem::GRAPHICS);

      swapBuffers();
    }
    else if (id == m_physicsLoop)
    {
      // Model controls
      float engine = m_simControls->analog(A_ENGINE);
      float roll = m_simControls->analog(A_ROLL);
      float pitch = -m_simControls->analog(A_PITCH);
      float yaw = -m_simControls->analog(A_YAW);
      float throttle = m_simControls->analog(A_THROT);

      m_aircraft->setEngineSpeed(engine);
      m_aircraft->setControls(throttle, pitch, roll, yaw);

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
      g_log.info("Performance statistics:\n" + m_profiler->outputAsString());
    }
  }

  /**
   * @copydoc Game::gameShutdown
   */
  void DemoGame::gameShutdown()
  {
    ConfigurableGame::gameShutdown();

    m_audioContext->close();
  }

  /**
   * @copydoc ConfigurableGame::setDefaultConfigOptions
   */
  void DemoGame::setDefaultConfigOptions()
  {
    KVNode &root = this->root();

    KVNode aircraft("aircraft");
    aircraft.set("selected", "Gaui X5");
    root.addChild(aircraft);

    KVNode terrain("terrain");
    terrain.set("default_model", "Flat");
    root.addChild(terrain);

    KVNode telemetry("telemetry");
    telemetry.set("enable", "false");
    telemetry.set("protocol", "frsky_sport_uart_bridge");
    telemetry.set("port", "COM1");
    telemetry.set("baud", "115200");
    root.addChild(telemetry);
  }
}
}