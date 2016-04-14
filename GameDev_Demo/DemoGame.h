/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _GAMEDEV_DEMO_DEMOGAME_H_
#define _GAMEDEV_DEMO_DEMOGAME_H_

#include <Engine_Common/ConfigurableGame.h>

#include <SDL_ttf.h>

#include <Engine_Audio/Context.h>
#include <Engine_Audio/Listener.h>
#include <Engine_Audio/Source.h>
#include <Engine_Common/Scene.h>
#include <Engine_Common/SceneObject.h>
#include <Engine_Graphics/RenderableObject.h>
#include <Engine_Graphics/ShaderProgram.h>
#include <Engine_Input/IControlScheme.h>
#include <Engine_Physics/PhysicalSystem.h>
#include <Engine_UIMenu/IMenu.h>

#include "Aircraft.h"

namespace GameDev
{
namespace Demo
{
  /**
   * @class DemoGame
   * @brief Game demonstrating features of the game engine.
   * @author Dan Nixon
   */
  class DemoGame : public Engine::Common::ConfigurableGame
  {
  public:
    DemoGame();
    virtual ~DemoGame();

  protected:
    virtual int gameStartup();
    virtual void gameLoop(Uint8 id, float dtMilliSec);
    virtual void gameShutdown();
    virtual void setDefaultConfigOptions();

  private:
    friend class OptionsMenu;

    Uint8 m_graphicsLoop;
    Uint8 m_physicsLoop;
    Uint8 m_audioLoop;
    Uint8 m_profileLoop;

    TTF_Font *m_font;

    Engine::Graphics::ShaderProgram *m_sp;
    Engine::Graphics::ShaderProgram *m_uiShader;

    Engine::Graphics::RenderableObject *m_leftStick;
    Engine::Graphics::RenderableObject *m_rightStick;

    Engine::Maths::Matrix4 m_losPMatrix; //!< Perspective matrix for line of sight flying
    Engine::Maths::Matrix4 m_fpvPMatrix; //!< Perspective matrix for first person view flying
    Engine::Common::Scene *m_s;          //!< Scene containing world (terrain and models)
    Engine::Common::Scene *m_ui;         //!< Scene containing UI
    Engine::UIMenu::IMenu *m_menu;

    Engine::Audio::Context *m_audioContext;
    Engine::Audio::Listener *m_audioListener;
    Engine::Audio::Source *m_audioSource1;
    Engine::Audio::Source *m_audioSource2;

    Engine::Common::SceneObject *m_model;

    Engine::Input::IControlScheme *m_simControls;

    Engine::Physics::PhysicalSystem *m_physicalSystem;
    Engine::Physics::RigidBody *m_modelBody;
  };
}
}

#endif