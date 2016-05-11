/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "OptionsMenu.h"

#include <Engine_Utility/StringUtils.h>

using namespace Engine::Common;
using namespace Engine::Maths;
using namespace Engine::UIMenu;
using namespace Engine::Utility;

namespace GameDev
{
namespace FlightSim
{
  /**
   * @copydoc TopBarMenu::TopBarMenu
   */
  OptionsMenu::OptionsMenu(Game *game, TTF_Font *font, float textSize)
      : TopBarMenu(game, font, textSize)
  {
    setMargin(Vector2());

    addNewItem(nullptr, "exit", "Exit");
    m_pauseOption = addNewItem(nullptr, "pause", "Pause");
    addNewItem(nullptr, "reset", "Reset");

    MenuItem *cameraMenu = addNewItem(nullptr, "camera", "Camera");
    addNewItem(cameraMenu, "los", "Line of Sight");
    addNewItem(cameraMenu, "fpv", "First Person View");

    MenuItem *uiMenu = addNewItem(nullptr, "ui", "HUD");
    m_telemetryOption = addNewItem(uiMenu, "telemetry", "Telemetry");
    m_sticksOption = addNewItem(uiMenu, "sticks", "Sticks");

    m_aircraftMenu = addNewItem(nullptr, "aircraft", "Aircraft");
    m_terrainMenu = addNewItem(nullptr, "terrain", "Terrain");
  }

  OptionsMenu::~OptionsMenu()
  {
  }

  /**
   * @brief Populates the aircraft list.
   * @param items List of aircraft
   */
  void OptionsMenu::populateAircraftMenu(const NameValueList &items)
  {
    populateMenu(m_aircraftMenu, items);
  }

  /**
   * @brief Populates the terrain list.
   * @param items List of terrains
   */
  void OptionsMenu::populateTerrainMenu(const NameValueList &items)
  {
    populateMenu(m_terrainMenu, items);
  }

  /**
   * @copydoc IMenu::handleMenuOptionSelection
   */
  void OptionsMenu::handleMenuOptionSelection(Engine::UIMenu::MenuItem *item)
  {
    if (item->name() == "exit")
    {
      m_game->exit();
    }
    else if (item->name() == "pause")
    {
      m_game->messageQueue().push(std::make_pair(Subsystem::GAME_LOGIC, "simulation:toggle"));
    }
    else if (item->name() == "reset")
    {
      m_game->messageQueue().push(std::make_pair(Subsystem::GAME_LOGIC, "aircraft:reset"));
    }
    else if (item->parent()->name() == "camera")
    {
      m_game->messageQueue().push(std::make_pair(Subsystem::GAME_LOGIC, "camera:mode:" + item->name()));
    }
    else if (item->name() == "telemetry")
    {
      m_game->messageQueue().push(std::make_pair(Subsystem::GAME_LOGIC, "telemetry:toggle"));
    }
    else if (item->name() == "sticks")
    {
      m_game->messageQueue().push(std::make_pair(Subsystem::GAME_LOGIC, "sticks:toggle"));
    }
    else if (item->parent()->name() == "aircraft")
    {
      m_game->messageQueue().push(std::make_pair(Subsystem::GAME_LOGIC, "aircraft:select:" + item->name()));
    }
    else if (item->parent()->name() == "terrain")
    {
      m_game->messageQueue().push(std::make_pair(Subsystem::GAME_LOGIC, "terrain:renew:" + item->name()));
    }
  }

  /**
   * @brief Adds a set of new items to a given list node.
   * @param parent Parent menu item
   * @param items List of new items
   */
  void OptionsMenu::populateMenu(Engine::UIMenu::MenuItem *parent, const NameValueList &items)
  {
    for (auto it = items.begin(); it != items.end(); ++it)
      addNewItem(parent, it->second, it->first);
  }

  /**
   * @copydoc GraphicalScene::update
   */
  void OptionsMenu::update(float msec, Subsystem sys)
  {
    GraphicalScene::update(msec, sys);

    if (sys == Subsystem::GRAPHICS && m_game->messageQueue().hasMessage(Subsystem::UI_MENU))
    {
      std::vector<std::string> messageOptions = StringUtils::Split(m_game->messageQueue().pop(Subsystem::UI_MENU).second, ':');

      // Update the name of a menu item
      if (messageOptions.size() == 3 && messageOptions[0] == "menu")
      {
        if (messageOptions[1] == "telemetry_option")
        {
          m_telemetryOption->setText(messageOptions[2]);
          layout();
        }
        else if (messageOptions[1] == "sticks_option")
        {
          m_sticksOption->setText(messageOptions[2]);
          layout();
        }  
        else if (messageOptions[1] == "pause")
        {
          m_pauseOption->setText(messageOptions[2]);
          layout();
        }
      }
    }
  }
}
}
