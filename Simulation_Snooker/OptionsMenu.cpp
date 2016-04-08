/**
 * @file
 * @author Dan Nixon
 */

#include "OptionsMenu.h"

#include "SnookerControls.h"
#include "SnookerSimulation.h"

using namespace Engine::Common;
using namespace Engine::UIMenu;
using namespace Engine::Input;

namespace Simulation
{
namespace Snooker
{
  /**
   * @copydoc TopBarMenu::TopBarMenu
   */
  OptionsMenu::OptionsMenu(Game *game, TTF_Font *font, float textSize, SnookerSimulation *simulation)
      : TopBarMenu(game, font, textSize)
      , m_simulation(simulation)
  {
    MenuItem *root = addNewItem(nullptr, "menu", "Menu");

    // Items
    m_pause = addNewItem(root, "pause", "Pause (P)");
    m_profile = addNewItem(root, "show_profile_data", "Show profile data (F)");
    m_mode = addNewItem(root, "mode", "Mode: Sandbox");
    addNewItem(root, "reset", "Reset (R)");
    addNewItem(root, "exit", "Exit");
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
    else if (item == m_mode)
    {
      m_simulation->controls->setState(S_MODE_CHANGE, true);
    }
    else if (item == m_pause)
    {
      m_simulation->controls->flipState(S_PAUSE);
    }
    else if (item == m_profile)
    {
      m_simulation->controls->flipState(S_PROFILE_DISPLAY);
    }
    else if (item->name() == "reset")
    {
      m_simulation->controls->setState(S_RESET, true);
    }
  }

  /**
   * @brief Updates the text shown on menu options to respect the current state.
   */
  void OptionsMenu::updateTextFromState()
  {
    m_pause->setText(m_simulation->controls->state(S_PAUSE) ? "Resume (P)" : "Pause (P)");
    m_profile->setText(m_simulation->controls->state(S_PROFILE_DISPLAY) ? "Hide profile data (F)"
                                                                        : "Show profile data (F)");
    m_mode->setText(m_simulation->fsm.activeStateBranch()[0]->name() == "game" ? "Mode: Game" : "Mode: Sandbox");
  }
}
}
