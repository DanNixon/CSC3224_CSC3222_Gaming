/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

//#define PHYSICS_DEBUG_DRAW
#define PROFILE

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
using namespace Engine::ResourceManagment;

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

    ShaderProgram *terrainShader = new ShaderProgram();
    terrainShader->addShader(new VertexShader("../resources/shader/vert_terrain.glsl"));
    terrainShader->addShader(new FragmentShader("../resources/shader/frag_tex.glsl"));
    terrainShader->link();
    ShaderProgramLookup::Instance().add("terrain_shader", terrainShader);

    ShaderProgram *menuShader = new ShaderProgram();
    menuShader = new ShaderProgram();
    menuShader->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
    menuShader->addShader(new FragmentShader("../resources/shader/frag_tex.glsl"));
    menuShader->link();
    ShaderProgramLookup::Instance().add("menu_shader", menuShader);
    ShaderProgramLookup::Instance().add("aircraft_shader_tex", menuShader);

    // Load textures
    Texture *terrainTex = new Texture();
    terrainTex->load("../resources/terrain_height.png");
    TextureLookup::Instance().add("terrain_texture", terrainTex);

    // Create menu
    m_menu = new OptionsMenu(this, TTFFontLookup::Instance().get("main_font"), 0.05f);
    m_menu->setMargin(Vector2(0.005f, 0.005f));

    // Load aircraft
    loadAircraft();

    // Load terrain presets
    loadTerrainPresets();

    // Init menu
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
    m_physicalSystem = new FSPhysicalSystem(8.33f, 83.33f, 100.0f, this); // At best 120Hz, at worst 12Hz
#ifdef PHYSICS_DEBUG_DRAW
    m_physicsDebugDraw = new DebugDrawEngine(ShaderProgramLookup::Instance().get("ui_shader"));
    m_physicsDebugDraw->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    m_physicalSystem->world()->setDebugDrawer(m_physicsDebugDraw);
    m_s->root()->addChild(m_physicsDebugDraw);
#endif

    // Initial aircraft
    selectAircraft(m_rootKVNode.child("aircraft").keyString("selected"), true);

    // Line of fight camera
    m_lineOfSightCamera =
        new Camera("line_of_sight_camera", Matrix4::Perspective(1.0f, 500000.0f, windowAspect(), 30.0f));
    m_lineOfSightCamera->setModelMatrix(
        Matrix4::Translation(m_rootKVNode.child("camera").keyVector3("los_camera_position")));
    m_lineOfSightCamera->lookAt(m_activeAircraft);
    m_s->root()->addChild(m_lineOfSightCamera);

    // Aerial camera
    m_aerialCamera = new Camera("aerial_camera", Matrix4::Perspective(1.0f, 500000.0f, windowAspect(), 30.0f));
    m_aerialCamera->setModelMatrix(
        Matrix4::Translation(m_rootKVNode.child("camera").keyVector3("aerial_camera_position")));
    m_aerialCamera->lookAt(m_activeAircraft);
    m_s->root()->addChild(m_aerialCamera);

    // Default camera mode
    setCameraMode(m_rootKVNode.children()["camera"].keys()["mode"]);

    // Initial terrain
    renewTerrain(m_rootKVNode.child("terrain").keyString("default_type"));

    // GL setup
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.3f, 0.5f, 1.0f);

    // Max terrain height
    glUniform1f(glGetUniformLocation(terrainShader->program(), "maxHeight"), 1.0f / 100000.0f);

    // Input
    if (JoystickHandler::NumJoysticks() > 0 && m_rootKVNode.child("joystick").keyBool("enable"))
    {
      g_log.info("Using joystick and keyboard");
      m_simControls = new KJSSimulatorControls(this, m_rootKVNode.child("joystick"));
      m_simControls->setAnalogDeadbands(0.05f);
      if (!static_cast<KJSSimulatorControls *>(m_simControls)->joystick()->open(m_rootKVNode.child("joystick").keyUnsignedLong("number")))
      {
        g_log.error("Could not open joystick");
        return 50;
      }
    }
    else
    {
      g_log.info("Using mouse and keyboard");
      m_simControls = new KMSimulatorControls(this);
      m_simControls->setAnalogDeadbands(0.05f);
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
#ifdef PROFILE
    m_profileLoop = addTimedLoop(1000.0f, "profile");
#endif

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

      m_activeAircraft->setEngineSpeed(engine);
      m_activeAircraft->setControls(throttle, pitch, roll, yaw);

      // Physics update
      m_activeAircraft->update(dtMilliSec, Subsystem::PHYSICS);
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
      float rssi = (float)m_activeAircraft->rssi();
      float vbat = m_activeAircraft->batteryVoltage();
      float current = m_activeAircraft->batteryCurrent();
      float altitude = m_activeAircraft->altitude();

      // Kill on low RSSI
      if (rssi < 25)
        m_activeAircraft->activateFailsafe();

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
          m_activeAircraft->reset();
        }
        else if (msgStr.find("simulation:toggle") != std::string::npos)
        {
          bool running = !m_physicalSystem->simulationRunning();
          m_physicalSystem->setSimulationState(running);

          // Update menu text
          std::string msg = "menu:pause:Resume";
          if (running)
            msg = "menu:pause:Pause";
          m_msgQueue.push(MessageQueue::MessageType(Subsystem::UI_MENU, msg));
        }
        else if (msgStr.find("camera:mode:") != std::string::npos)
        {
          std::vector<std::string> options = StringUtils::Split(msgStr, ':');
          setCameraMode(options[2]);
        }
        else if (msgStr.find("aircraft:select:") != std::string::npos)
        {
          std::vector<std::string> options = StringUtils::Split(msgStr, ':');
          selectAircraft(options[2]);
        }
        else if (msgStr.find("terrain:renew:") != std::string::npos)
        {
          std::vector<std::string> options = StringUtils::Split(msgStr, ':');
          renewTerrain(options[2]);
        }
        else if (msgStr.find("telemetry:toggle") != std::string::npos)
        {
          bool visible = StringUtils::ToBool(m_rootKVNode.children()["hud"].keys()["show_telemetry"]);
          setTelemetryVisible(!visible);
        }
        else if (msgStr.find("sticks:toggle") != std::string::npos)
        {
          bool visible = StringUtils::ToBool(m_rootKVNode.children()["hud"].keys()["show_sticks"]);
          setSticksVisible(!visible);
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
    aircraft.keys()["selected"] = "Gaui_X7";
    aircraft.keys()["default_rotation"] = "135";
    aircraft.keys()["default_position"] = "[0, 50, -250]";
    node.addChild(aircraft);

    KVNode terrain("terrain");
    terrain.keys()["default_type"] = "flat.ini";
    node.addChild(terrain);

    KVNode camera("camera");
    camera.keys()["mode"] = "los";
    camera.keys()["los_camera_position"] = "[0,250,0]";
    camera.keys()["aerial_camera_position"] = "[0,5000,5000]";
    node.addChild(camera);

    KVNode hud("hud");
    hud.keys()["show_telemetry"] = "false";
    hud.keys()["show_sticks"] = "false";
    node.addChild(hud);

    KVNode joystick("joystick");
    joystick.keys()["enable"] = "true";
    joystick.keys()["number"] = "0";
    joystick.keys()["axis_collective"] = "2";
    joystick.keys()["axis_yaw"] = "3";
    joystick.keys()["axis_pitch"] = "1";
    joystick.keys()["axis_roll"] = "0";
    joystick.keys()["axis_throttle"] = "4";
    node.addChild(joystick);

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

  void FlightSimGame::loadTerrainPresets()
  {
    std::vector<std::string> terrainNames =
        DiskUtils::ListDirectory(m_rootKVNode.child("resources").keyString("terrains"), true, false);

    OptionsMenu::NameValueList menuItems;

    for (auto it = terrainNames.begin(); it != terrainNames.end(); ++it)
    {
      TerrainBuilder *terrain = new TerrainBuilder(*it, m_rootKVNode.child("resources").keyString("terrains"));
      terrain->loadMetadata();

      if (terrain->rootKVNode().child("general").keyBool("enabled"))
      {
        m_terrainBuilders.push_back(terrain);
        menuItems.push_back(std::make_pair(terrain->displayName(), terrain->name()));
      }
      else
      {
        MemoryManager::Instance().release(terrain);
      }
    }

    m_menu->populateTerrainMenu(menuItems);
  }

  void FlightSimGame::loadAircraft()
  {
    std::vector<std::string> aircraftNames =
        DiskUtils::ListDirectory(m_rootKVNode.child("resources").keyString("models"), false, true);

    OptionsMenu::NameValueList menuItems;

    for (auto it = aircraftNames.begin(); it != aircraftNames.end(); ++it)
    {
      Aircraft *aircraft = new Aircraft(*it, m_rootKVNode.child("resources").keyString("models"));
      aircraft->loadMetadata();

      if (aircraft->rootKVNode().child("general").keyBool("enabled"))
      {
        m_aircraft.push_back(aircraft);
        menuItems.push_back(std::make_pair(aircraft->displayName(), aircraft->name()));
      }
      else
      {
        MemoryManager::Instance().release(aircraft);
      }
    }

    m_menu->populateAircraftMenu(menuItems);
  }

  void FlightSimGame::selectAircraft(const std::string &name, bool force)
  {
    // No nothing if this is already the active aircraft
    if (m_rootKVNode.child("aircraft").keyString("selected") == name && !force)
      return;

    // Record option
    m_rootKVNode.children()["aircraft"].keys()["selected"] = name;

    // Find new aircraft
    auto it = std::find_if(m_aircraft.begin(), m_aircraft.end(), [name](Aircraft *a) { return a->name() == name; });
    if (it == m_aircraft.end())
    {
      g_log.error("Aircraft " + name + " not found");
      return;
    }

    // Remove old aircraft
    if (m_activeAircraft != nullptr)
      m_s->root()->removeChild(m_activeAircraft);

    // Setup aircraft
    float aircraftRotation = m_rootKVNode.child("aircraft").keyFloat("default_rotation");
    Vector3 aircraftPosition = m_rootKVNode.child("aircraft").keyVector3("default_position");

    (*it)->loadMeshes();
    (*it)->loadAudio(m_audioListener);
    (*it)->initPhysics(aircraftPosition, Quaternion(aircraftRotation, 0.0f, 0.0f));
    (*it)->initCamera(this);

    // Set active aircraft
    m_activeAircraft = *it;

    // Add new aircraft
    m_s->root()->addChild(m_activeAircraft);
    m_physicalSystem->setActiveAircraft(m_activeAircraft);
    m_activeAircraft->reset();
  }

  void FlightSimGame::renewTerrain(const std::string &name)
  {
    // Record option
    m_rootKVNode.children()["terrain"].keys()["default_type"] = name;

    // Find new terrain generator
    auto it = std::find_if(m_terrainBuilders.begin(), m_terrainBuilders.end(),
                           [name](TerrainBuilder *a) { return a->name() == name; });
    if (it == m_terrainBuilders.end())
    {
      g_log.error("Terrain builder " + name + " not found");
      return;
    }

    Terrain *oldTerrain = m_terrain;

    // Generate new terrain
    m_terrain = new Terrain("terrain");
    (*it)->generate(m_terrain);

    // Add new terrain
    m_s->root()->addChild(m_terrain);
    m_physicalSystem->setActiveTerrain(m_terrain);

    // Remove old terrain
    if (oldTerrain != nullptr)
    {
      m_s->root()->removeChild(oldTerrain);
      MemoryManager::Instance().release(oldTerrain);
    }
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
    m_activeAircraft->fpvCamera()->setActive(true);
    m_lineOfSightCamera->setActive(false);
    m_aerialCamera->setActive(false);

    // Update active camera
    if (mode == "fpv")
      m_activeAircraft->fpvCamera()->setActive(true);
    else if (mode == "aerial")
      m_aerialCamera->setActive(true);
    else
      m_lineOfSightCamera->setActive(true);

    // Record setting
    m_rootKVNode.children()["camera"].keys()["mode"] = mode;
  }

  /**
   * @brief Sets the visibility of the telemetry indicators.
   * @param visible Visibility
   */
  void FlightSimGame::setTelemetryVisible(bool visible)
  {
    // Set visibility
    m_onScreenTelemetry->setActive(visible);

    // Store option
    m_rootKVNode.children()["hud"].keys()["show_telemetry"] = visible ? "true" : "false";

    // Update menu option text
    std::string msg = "menu:telemetry_option:Show Telemetry";
    if (visible)
      msg = "menu:telemetry_option:Hide Telemetry";
    m_msgQueue.push(MessageQueue::MessageType(Subsystem::UI_MENU, msg));
  }

  /**
   * @brief Sets the visibility of the stick position indicators.
   * @param visible Visibility
   */
  void FlightSimGame::setSticksVisible(bool visible)
  {
    // Set visibility
    m_leftStickIndicator->setActive(visible);
    m_rightStickIndicator->setActive(visible);

    // Store option
    m_rootKVNode.children()["hud"].keys()["show_sticks"] = visible ? "true" : "false";

    // Update menu option text
    std::string msg = "menu:sticks_option:Show Sticks";
    if (visible)
      msg = "menu:sticks_option:Hide Sticks";
    m_msgQueue.push(MessageQueue::MessageType(Subsystem::UI_MENU, msg));
  }
}
}
