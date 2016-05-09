/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

//#define PHYSICS_DEBUG_DRAW

#include "FlightSimGame.h"

#include <sstream>

#include <Engine_Audio/WAVSource.h>
#include <Engine_Common/Profiler.h>
#include <Engine_Graphics/GraphicalScene.h>
#include <Engine_Graphics/HeightmapMesh.h>
#include <Engine_Graphics/Light.h>
#include <Engine_Graphics/ModelLoader.h>
#include <Engine_Graphics/RectangleMesh.h>
#include <Engine_Graphics/Shaders.h>
#include <Engine_Graphics/SphericalMesh.h>
#include <Engine_IO/DiskUtils.h>
#include <Engine_IO/KVNode.h>
#include <Engine_Logging/FileOutputChannel.h>
#include <Engine_Logging/Logger.h>
#include <Engine_Maths/Quaternion.h>
#include <Engine_Physics/BoundingBoxShape.h>
#include <Engine_Physics/ConvexHullShape.h>
#include <Engine_Physics/Heightmap.h>
#include <Engine_ResourceManagment/MemoryManager.h>
#include <Engine_Utility/StringUtils.h>

#include "FrSkySPORTBridgeTelemetry.h"
#include "KJSSimulatorControls.h"
#include "KMSimulatorControls.h"
#include "SerialPort.h"
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
using namespace Engine::Utility;

namespace
{
Logger g_log(__FILE__);
}

namespace GameDev
{
namespace FlightSim
{
  /**
   * @brief Creates a new demonstration game instance.
   */
  FlightSimGame::FlightSimGame()
      : Game("Flight Sim", std::make_pair(1024, 768))
      , m_physicalTelemetry(nullptr)
  {
  }

  FlightSimGame::~FlightSimGame()
  {
  }

  void FlightSimGame::selectAircraft(const std::string &name)
  {
    // Record option
    m_rootKVNode.children()["aircraft"].keys()["selected"] = name;

    // TODO
  }

  void FlightSimGame::renewTerrain(const std::string &name)
  {
    // Record option
    m_rootKVNode.children()["terrain"].keys()["default_type"] = name;

    // TODO
  }

  /**
   * @brief Sets the camera mode.
   * @param mode Mode string
   *
   * Expected mode strings are either "fpv" for first person view or "los" for
   * line of sight.
   */
  void FlightSimGame::setCameraMode(const std::string &mode)
  {
    // Update active camera
    bool fpv = mode == "fpv";
    m_aircraft->fpvCamera()->setActive(fpv);
    m_lineOfSightCamera->setActive(!fpv);

    // Record setting
    m_rootKVNode.children()["camera"].keys()["mode"] = mode;
  }

  /**
   * @brief Sets the visibility of the telemetry indicators.
   * @param visible Visibility
   */
  void FlightSimGame::setTelemetryVisible(bool visible)
  {
    m_onScreenTelemetry->setActive(visible);
    m_rootKVNode.children()["hud"].keys()["show_telemetry"] = visible ? "true" : "false";
  }

  /**
   * @brief Sets the visibility of the stick position indicators.
   * @param visible Visibility
   */
  void FlightSimGame::setSticksVisible(bool visible)
  {
    m_leftStickIndicator->setActive(visible);
    m_rightStickIndicator->setActive(visible);
    m_rootKVNode.children()["hud"].keys()["show_sticks"] = visible ? "true" : "false";
  }

  /**
   * @copydoc Game::gameStartup
   */
  int FlightSimGame::gameStartup()
  {
    // Open file logger
    FileOutputChannel *fileLog = new FileOutputChannel(gameSaveDirectory() + "FlightSimLog.log");
    fileLog->open();
    LoggingService::Instance().addOutput(fileLog);

    //!< \todo Display dismissible on screen scontrols
    if (isFirstRun())
    {
      g_log.info("This is the first time the game has been launched.");
    }

    // Load fonts
    TTFFontLookup::Instance().add("main_font", TTF_OpenFont("../resources/open-sans/OpenSans-Regular.ttf", 20));

    // Load shaders
    ShaderProgram *aircraftShaderLit = new ShaderProgram();
    aircraftShaderLit->addShader(new VertexShader("../resources/shader/vert_lighting.glsl"));
    aircraftShaderLit->addShader(new FragmentShader("../resources/shader/frag_lighting.glsl"));
    aircraftShaderLit->link();
    ShaderProgramLookup::Instance().add("aircraft_shader_lit", aircraftShaderLit);

    ShaderProgram *uiShader = new ShaderProgram();
    uiShader->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
    uiShader->addShader(new FragmentShader("../resources/shader/frag_col.glsl"));
    uiShader->link();
    ShaderProgramLookup::Instance().add("ui_shader", uiShader);

    // TODO
    ShaderProgramLookup::Instance().add("terrain_shader", uiShader);

    ShaderProgram *menuShader = new ShaderProgram();
    menuShader = new ShaderProgram();
    menuShader->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
    menuShader->addShader(new FragmentShader("../resources/shader/frag_tex.glsl"));
    menuShader->link();
    ShaderProgramLookup::Instance().add("menu_shader", menuShader);
    ShaderProgramLookup::Instance().add("aircraft_shader_tex", menuShader);

    // Menu
    m_menu = new OptionsMenu(this, TTFFontLookup::Instance().get("main_font"), 0.05f);
    m_menu->setMargin(Vector2(0.005f, 0.005f));
    m_menu->populateAircraftMenu({{"Gaui X5", "gaui_x5"}, {"Logo 600", "logo_600"}});
    m_menu->populateTerrainMenu({{"Flat", "flat"}, {"Tall Peaks", "peaks"}, {"Forest", "forest"}});
    m_menu->layout();
    m_menu->hide();
    addEventHandler(m_menu);

    // UI
    m_ui = new GraphicalScene(new SceneObject("root"), Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -1)),
                              Matrix4::Orthographic(0.0f, -1.0f, 10.0f, -10.0f, 10.0f, -10.0f));

    // UI: stick position indicators
    m_leftStickIndicator = new StickIndicator("left_stick", m_ui->root());
    m_leftStickIndicator->setModelMatrix(Matrix4::Translation(Vector3(-8.5f, -8.5f, 0.9f)));
    m_rightStickIndicator = new StickIndicator("right_stick", m_ui->root());
    m_rightStickIndicator->setModelMatrix(Matrix4::Translation(Vector3(8.5f, -8.5f, 0.9f)));

    // UI: On screen telemetry
    m_onScreenTelemetry = new OnScreenTelemetry(m_ui->root());
    m_onScreenTelemetry->setModelMatrix(Matrix4::Translation(Vector3(8.5f, 0.0f, 0.9f)));
    m_onScreenTelemetry->m_rssi->setAlarmLevels(
        std::stof(m_rootKVNode.children()["on_screen_telemetry"].keys()["rssi_low"]),
        std::stof(m_rootKVNode.children()["on_screen_telemetry"].keys()["rssi_critical"]));

    // UI: set default state
    setTelemetryVisible(StringUtils::ToBool(m_rootKVNode.children()["hud"].keys()["show_telemetry"]));
    setSticksVisible(StringUtils::ToBool(m_rootKVNode.children()["hud"].keys()["show_sticks"]));

    // Scene
    m_s = new GraphicalScene(new SceneObject("root"));

    // Light
    Light *sun = new Light("sun", 20000.0f);
    sun->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 1000.0f, 0.0f)));
    m_s->root()->addChild(sun);
    m_s->lights().push_back(sun);

    // Audio
    m_audioContext = new Context();
    m_audioContext->open();
    m_audioListener = new Listener("audio_listener");
    m_s->root()->addChild(m_audioListener);

    // Physics
    m_physicalSystem = new PhysicalSystem(8.33f, 83.33f); // At best 120Hz, at worst 12Hz
#ifdef PHYSICS_DEBUG_DRAW
    m_physicsDebugDraw = new DebugDrawEngine(ShaderProgramLookup::Instance().get("ui_shader"));
    m_physicsDebugDraw->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    m_physicalSystem->world()->setDebugDrawer(m_physicsDebugDraw);
    m_s->root()->addChild(m_physicsDebugDraw);
#endif

    // TODO
    std::vector<std::string> a =
        DiskUtils::ListDirectory(m_rootKVNode.child("resources").keyString("models"), false, true);
    std::vector<std::string> t =
        DiskUtils::ListDirectory(m_rootKVNode.child("resources").keyString("terrains"), true, false);

    // Aircraft
    float aircraftRotation = std::stof(m_rootKVNode.children()["aircraft"].keys()["default_rotation"]);
    Vector3 aircraftPosition;
    std::stringstream aircraftPositionStr(m_rootKVNode.children()["aircraft"].keys()["default_position"]);
    aircraftPositionStr >> aircraftPosition;

    m_aircraft = new Aircraft("Gaui_X7", m_rootKVNode.child("resources").keyString("models"));
    m_aircraft->loadMetadata();
    m_aircraft->loadMeshes();
    m_aircraft->loadAudio(m_audioListener);
    m_aircraft->initPhysics(m_physicalSystem, aircraftPosition, Quaternion(aircraftRotation, 0.0f, 0.0f));
    m_aircraft->initCamera(this);
    m_s->root()->addChild(m_aircraft);

    // Terrain
    m_terrain = new Terrain("terrain", 10000.0f, 10000.0f);
    m_terrain->initPhysics(m_physicalSystem);
    m_s->root()->addChild(m_terrain);

    // Camera
    m_lineOfSightCamera =
        new Camera("line_of_sight_camera", Matrix4::Perspective(1.0f, 50000.0f, windowAspect(), 30.0f));
    m_lineOfSightCamera->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 250.0f, 0.0f)));
    m_lineOfSightCamera->lookAt(m_aircraft);
    m_s->root()->addChild(m_lineOfSightCamera);

    // Default camera mode
    setCameraMode(m_rootKVNode.children()["camera"].keys()["mode"]);

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

    // Physical telemetry
    KVNode &telem = m_rootKVNode.children()["telemetry"];
    if (StringUtils::ToBool(telem.keys()["enable"]) && telem.keys()["protocol"] == "frsky_sport_uart_bridge")
    {
      SerialPort *port = new SerialPort();
      if (port->open(telem.keys()["port"], std::stoi(telem.keys()["baud"])))
      {
        m_physicalTelemetry = new FrSkySPORTBridgeTelemetry(port);
        m_physicalTelemetry->send();
      }
      else
        g_log.warn("Could not open serial port, no physical telemetry");
    }

    // Timed loops
    m_graphicsLoop = addTimedLoop(16.66f, "graphics");
    m_physicsLoop = addTimedLoop(8.33f, "physics");
    m_audioLoop = addTimedLoop(16.66f, "audio");
    m_uiLoop = addTimedLoop(100.0f, "ui_updates");
    m_telemetryLoop = addTimedLoop(100.0f, "telemetry");
    m_queueLoop = addTimedLoop(100.0f, "queue_processing");
    m_profileLoop = addTimedLoop(1000.0f, "profile");

    // Profiling
    m_profiler = new Profiler(this);

    return 0;
  }

  /**
   * @copydoc Game::gameLoop
   */
  void FlightSimGame::gameLoop(Uint8 id, float dtMilliSec)
  {
    if (id == m_graphicsLoop)
    {
// Graphics update
#ifdef PHYSICS_DEBUG_DRAW
      m_physicalSystem->world()->debugDrawWorld();
#endif
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
    else if (id == m_uiLoop)
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
    }
    else if (id == m_telemetryLoop)
    {
      float rssi = (float)m_aircraft->rssi();
      float vbat = m_aircraft->batteryVoltage();
      float current = m_aircraft->batteryCurrent();
      float altitude = m_aircraft->altitude();

      // On screen telemetry
      m_onScreenTelemetry->setValue(TelemetryValue::RSSI, rssi);
      m_onScreenTelemetry->setValue(TelemetryValue::VBAT, vbat);
      m_onScreenTelemetry->setValue(TelemetryValue::CURRENT, current);
      m_onScreenTelemetry->setValue(TelemetryValue::ALTITUDE, altitude);
      m_onScreenTelemetry->send();

      if (m_physicalTelemetry != nullptr)
      {
        // Update physical telemetry
        m_physicalTelemetry->setValue(TelemetryValue::RSSI, rssi);
        m_physicalTelemetry->setValue(TelemetryValue::VBAT, vbat);
        m_physicalTelemetry->setValue(TelemetryValue::CURRENT, current);
        m_physicalTelemetry->setValue(TelemetryValue::ALTITUDE, altitude);
        m_physicalTelemetry->send();
      }
    }
    else if (id == m_queueLoop)
    {
      if (m_msgQueue.hasMessage(Subsystem::GAME_LOGIC))
      {
        const std::string msgStr(m_msgQueue.pop(Subsystem::GAME_LOGIC).second);

        if (msgStr.find("aircraft:reset") != std::string::npos)
        {
          m_aircraft->reset();
        }
        else if (msgStr.find("simulation:toggle") != std::string::npos)
        {
          bool running = m_physicalSystem->simulationRunning();
          m_physicalSystem->setSimulationState(!running);
          // TODO: update menu text
        }
        else if (msgStr.find("camera:mode:") != std::string::npos)
        {
          // TODO
        }
        else if (msgStr.find("telemetry:toggle") != std::string::npos)
        {
          bool visible = StringUtils::ToBool(m_rootKVNode.children()["hud"].keys()["show_telemetry"]);
          setTelemetryVisible(!visible);
          m_menu->updateOptionNames();
        }
        else if (msgStr.find("sticks:toggle") != std::string::npos)
        {
          bool visible = StringUtils::ToBool(m_rootKVNode.children()["hud"].keys()["show_sticks"]);
          setSticksVisible(!visible);
          m_menu->updateOptionNames();
        }
      }
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
  void FlightSimGame::gameShutdown()
  {
    m_audioContext->close();
  }

  /**
   * @copydoc Game::defaultConfigOptions
   */
  void FlightSimGame::defaultConfigOptions(KVNode &node)
  {
    KVNode resources("resources");
    resources.keys()["models"] = "../resources/models/";
    resources.keys()["terrains"] = "../resources/terrain/";
    resources.keys()["shaders"] = "../resources/shades/";
    node.addChild(resources);

    KVNode aircraft("aircraft");
    aircraft.keys()["selected"] = "Gaui X5";
    aircraft.keys()["default_rotation"] = "135";
    aircraft.keys()["default_position"] = "[0, 50, -250]";
    node.addChild(aircraft);

    KVNode terrain("terrain");
    terrain.keys()["default_type"] = "Flat";
    node.addChild(terrain);

    KVNode camera("camera");
    camera.keys()["mode"] = "los";
    node.addChild(camera);

    KVNode lineOfSight("line_of_sight");
    lineOfSight.keys()["camera_height"] = "250";
    lineOfSight.keys()["pilot_collision_radius"] = "100";
    node.addChild(lineOfSight);

    KVNode hud("hud");
    hud.keys()["show_telemetry"] = "false";
    hud.keys()["show_sticks"] = "false";
    node.addChild(hud);

    KVNode onScreenTelemetry("on_screen_telemetry");
    onScreenTelemetry.keys()["rssi_low"] = "55";
    onScreenTelemetry.keys()["rssi_critical"] = "40";
    node.addChild(onScreenTelemetry);

    KVNode telemetry("telemetry");
    telemetry.keys()["enable"] = "false";
    telemetry.keys()["protocol"] = "frsky_sport_uart_bridge";
    telemetry.keys()["port"] = "COM1";
    telemetry.keys()["baud"] = "9600";
    node.addChild(telemetry);
  }
}
}
