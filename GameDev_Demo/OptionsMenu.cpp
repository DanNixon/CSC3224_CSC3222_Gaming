/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "OptionsMenu.h"

#include <Engine_Utility/StringUtils.h>

#include "DemoGame.h"

using namespace Engine::Common;
using namespace Engine::Maths;
using namespace Engine::UIMenu;
using namespace Engine::Utility;

namespace GameDev
{
namespace Demo
{
  /**
   * @copydoc TopBarMenu::TopBarMenu
   */
  OptionsMenu::OptionsMenu(Game *game, TTF_Font *font, float textSize)
      : TopBarMenu(game, font, textSize)
      , m_simulatorGame(dynamic_cast<DemoGame *>(m_game))
  {
    setMargin(Vector2());

    addNewItem(nullptr, "exit", "Exit");
    addNewItem(nullptr, "pause", "Pause");
    addNewItem(nullptr, "reset", "Reset");

    MenuItem *cameraMenu = addNewItem(nullptr, "camera", "Camera");
    addNewItem(cameraMenu, "los", "Line of Sight");
    addNewItem(cameraMenu, "fpv", "First Person View");

    MenuItem *uiMenu = addNewItem(nullptr, "ui", "HUD");
    m_telemetryOption = addNewItem(uiMenu, "telemetry", "Telemetry");
    m_sticksOption = addNewItem(uiMenu, "sticks", "Sticks");

    m_aircraftMenu = addNewItem(nullptr, "aircraft", "Aircraft");
    m_terrainMenu = addNewItem(nullptr, "terrain", "Terrain");

    // Update initial names
    updateOptionNames();
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
   * @brief Sets the names of certain menu options based on the state of the game.
   */
  void OptionsMenu::updateOptionNames()
  {
    bool showTelem = StringUtils::ToBool(m_simulatorGame->rootKVNode().children()["hud"].keys()["show_telemetry"]);
    bool showSticks = StringUtils::ToBool(m_simulatorGame->rootKVNode().children()["hud"].keys()["show_sticks"]);

    m_telemetryOption->setText(showTelem ? "Hide Telemetry" : "Show Telemetry");
    m_sticksOption->setText(showSticks ? "Hide Sticks" : "Show Sticks");
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
      auto system = m_simulatorGame->m_physicalSystem;
      bool run = !system->simulationRunning();
      system->setSimulationState(run);
      item->setText(run ? "Pause" : "Resume", true);
    }
    else if (item->parent()->name() == "camera")
    {
      dynamic_cast<DemoGame *>(m_game)->setCameraMode(item->name());
    }
    else if (item->name() == "telemetry")
    {
      bool state = !StringUtils::ToBool(m_simulatorGame->rootKVNode().children()["hud"].keys()["show_telemetry"]);
      m_simulatorGame->setTelemetryVisible(state);
      updateOptionNames();
    }
    else if (item->name() == "sticks")
    {
      bool state = !StringUtils::ToBool(m_simulatorGame->rootKVNode().children()["hud"].keys()["show_sticks"]);
      m_simulatorGame->setSticksVisible(state);
      updateOptionNames();
    }
    else if (item->parent()->name() == "aircraft")
    {
      std::string selectedAircraftName = item->name();
      m_simulatorGame->rootKVNode().children()["aircraft"].keys()["selected"] = selectedAircraftName;
    }
    else if (item->parent()->name() == "terrain")
    {
      std::string selectedAircraftName = item->name();
      m_simulatorGame->rootKVNode().children()["terrain"].keys()["default_model"] = selectedAircraftName;
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
}
}
