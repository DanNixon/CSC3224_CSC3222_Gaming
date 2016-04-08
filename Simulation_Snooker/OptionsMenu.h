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
  /**
   * @class OptionsMenu
   * @brief Menu used to display simulation options.
   * @author Dan Nixon
   */
  class OptionsMenu : public Engine::UIMenu::TopBarMenu
  {
  public:
    OptionsMenu(Engine::Common::Game *game, TTF_Font *font, float textSize, Engine::Input::IControlScheme *controls);
    virtual ~OptionsMenu();

    void updateTextFromControls();

  protected:
    virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);

  private:
    Engine::Input::IControlScheme *m_controls;

    Engine::UIMenu::MenuItem *m_pause;
    Engine::UIMenu::MenuItem *m_profile;
    Engine::UIMenu::MenuItem *m_mode;
  };
}
}

#endif
