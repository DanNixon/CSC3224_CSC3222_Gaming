/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
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
    typedef std::vector<std::pair<std::string, std::string>> NameValueList;

  public:
    OptionsMenu(Engine::Common::Game *game, TTF_Font *font, float textSize = 0.08f);
    virtual ~OptionsMenu();

    void populateAircraftMenu(const NameValueList &items);
    void populateTerrainMenu(const NameValueList &items);

  protected:
    virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);

  private:
    void populateMenu(Engine::UIMenu::MenuItem *parent, const NameValueList &items);

  private:
    Engine::UIMenu::MenuItem *m_aircraftMenu;
    Engine::UIMenu::MenuItem *m_terrainMenu;
  };
}
}

#endif
