/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_FLIGHTSIMGAME_H_
#define _GAMEDEV_FLIGHTSIM_FLIGHTSIMGAME_H_

#include <Engine_Common/Game.h>

#include <SDL_ttf.h>

#include <Engine_Audio/Context.h>
#include <Engine_Audio/Listener.h>
#include <Engine_Audio/Source.h>
#include <Engine_Common/Scene.h>
#include <Engine_Common/SceneObject.h>
#include <Engine_Graphics/Camera.h>
#include <Engine_Graphics/RenderableObject.h>
#include <Engine_Graphics/ShaderProgram.h>
#include <Engine_Input/IControlScheme.h>
#include <Engine_Physics/DebugDrawEngine.h>

#include "Aircraft.h"
#include "FSPhysicalSystem.h"
#include "ITelemetryProtocol.h"
#include "OnScreenTelemetry.h"
#include "OptionsMenu.h"
#include "StickIndicator.h"
#include "Terrain.h"
#include "TerrainBuilder.h"

namespace GameDev
{
namespace FlightSim
{
  /**
   * @class FlightSimGame
   * @brief Flight simulator game.
   * @author Dan Nixon
   */
  class FlightSimGame : public Engine::Common::Game
  {
  public:
    FlightSimGame();
    virtual ~FlightSimGame();

  protected:
    virtual int gameStartup();
    virtual void gameLoop(Uint8 id, float dtMilliSec);
    virtual void gameShutdown();
    virtual void defaultConfigOptions(Engine::IO::KVNode &node);

  private:
    void loadAircraft();
    void loadTerrainPresets();

    void selectAircraft(const std::string &name, bool force = false);
    void renewTerrain(const std::string &name);

    void setCameraMode(const std::string &mode);
    void setTelemetryVisible(bool visible);
    void setSticksVisible(bool visible);

  private:
    Uint8 m_graphicsLoop;
    Uint8 m_physicsLoop;
    Uint8 m_audioLoop;
    Uint8 m_uiLoop;
    Uint8 m_telemetryLoop;
    Uint8 m_queueLoop;
    Uint8 m_profileLoop;

    StickIndicator *m_leftStickIndicator;  //!< Indicator for position of left stick
    StickIndicator *m_rightStickIndicator; //!< Indicator for position of right stick

    Engine::Graphics::Camera *m_lineOfSightCamera; //!< Camera used for line of sight view
    Engine::Graphics::GraphicalScene *m_s;         //!< Scene containing world (terrain and models)
    Engine::Common::Scene *m_ui;                   //!< Scene containing UI

    OptionsMenu *m_menu; //!< Top bar option menu

    Engine::Audio::Context *m_audioContext;   //!< Audio context
    Engine::Audio::Listener *m_audioListener; //!< Audio listener

    Engine::Input::IControlScheme *m_simControls; //!< Active control scheme

    OnScreenTelemetry *m_onScreenTelemetry;  //!< On screen telemetry
    ITelemetryProtocol *m_physicalTelemetry; //!< Physical telemetry provider

    FSPhysicalSystem *m_physicalSystem;                   //!< Physics system
    Engine::Physics::DebugDrawEngine *m_physicsDebugDraw; //!< Physics debug draw engine

    std::vector<Aircraft *> m_aircraft; //!< All aircraft
    Aircraft *m_activeAircraft;         //!< Active aircraft

    std::vector<TerrainBuilder *> m_terrainBuilders; //!< Terrain builders
    Terrain *m_terrain; //!< Active terrain
  };
}
}

#endif
