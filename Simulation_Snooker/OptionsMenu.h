/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_SNOOKER_OPTIONSMENU_H_
#define _SIMULATION_SNOOKER_OPTIONSMENU_H_

#include <Engine_Common/Game.h>
#include <Engine_Input/IControlScheme.h>
#include <Engine_UIMenu/TopBarMenu.h>

namespace Simulation
{
namespace Snooker
{
  class SnookerSimulation;

  /**
   * @class OptionsMenu
   * @brief Menu used to display simulation options.
   * @author Dan Nixon
   */
  class OptionsMenu : public Engine::UIMenu::TopBarMenu
  {
  public:
    OptionsMenu(Engine::Common::Game *game, TTF_Font *font, float textSize, SnookerSimulation *simulation);
    virtual ~OptionsMenu();

    void updateTextFromState();

  protected:
    virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);

  private:
    SnookerSimulation *m_simulation;

    Engine::UIMenu::MenuItem *m_pause;
    Engine::UIMenu::MenuItem *m_profile;
    Engine::UIMenu::MenuItem *m_mode;
  };
}
}

#endif
