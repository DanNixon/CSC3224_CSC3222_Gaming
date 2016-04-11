/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "OptionsMenu.h"

#include "DemoGame.h"

using namespace Engine::Common;
using namespace Engine::UIMenu;

namespace GameDev
{
namespace Demo
{
  /**
   * @copydoc TopBarMenu::TopBarMenu
   */
  OptionsMenu::OptionsMenu(Game *game, TTF_Font *font, float textSize)
      : TopBarMenu(game, font, textSize)
  {
  }

  OptionsMenu::~OptionsMenu()
  {
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
      auto system = static_cast<DemoGame *>(m_game)->m_physicalSystem;
      bool run = !system->simulationRunning();
      system->setSimulationState(run);
      item->setText(run ? "Pause" : "Resume", true);
    }
    else if (item->parent()->name() == "aircraft")
    {
      std::string selectedAircraftName = item->name();
      dynamic_cast<ConfigurableGame *>(m_game)->root().child("aircraft").set("selected", selectedAircraftName);
    }
    else if (item->parent()->name() == "terrain")
    {
      std::string selectedAircraftName = item->name();
      dynamic_cast<ConfigurableGame *>(m_game)->root().child("terrain").set("default_model", selectedAircraftName);
    }

    // TODO
  }
}
}
