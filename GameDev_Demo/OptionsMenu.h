/**
 * @file
 * @author Dan Nixon
 */

#ifndef _GAMEDEV_DEMO_OPTIONSMENU_H_
#define _GAMEDEV_DEMO_OPTIONSMENU_H_

#include <Engine_Common/Game.h>
#include <Engine_UIMenu/TopBarMenu.h>

namespace GameDev
{
namespace Demo
{
  /**
   * @class OptionsMenu
   * @brief Menu used to display simulation options.
   * @author Dan Nixon
   */
  class OptionsMenu : public Engine::UIMenu::TopBarMenu
  {
  public:
    OptionsMenu(Engine::Common::Game *game, TTF_Font *font, float textSize = 0.08f);
    virtual ~OptionsMenu();

  protected:
    virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);
  };
}
}

#endif
