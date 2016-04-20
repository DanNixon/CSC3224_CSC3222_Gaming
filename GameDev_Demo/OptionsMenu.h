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
  class DemoGame;

  /**
   * @class OptionsMenu
   * @brief Menu used to display simulation options.
   * @author Dan Nixon
   */
  class OptionsMenu : public Engine::UIMenu::TopBarMenu
  {
  public:
    /**
     * @typedef NameValueList
     * @brief List of name and value pairs used for populating a submenu.
     */
    typedef std::vector<std::pair<std::string, std::string>> NameValueList;

  public:
    OptionsMenu(Engine::Common::Game *game, TTF_Font *font, float textSize);
    virtual ~OptionsMenu();

    void populateAircraftMenu(const NameValueList &items);
    void populateTerrainMenu(const NameValueList &items);

    void updateOptionNames();

  protected:
    virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);

  private:
    void populateMenu(Engine::UIMenu::MenuItem *parent, const NameValueList &items);

  private:
    DemoGame *m_simulatorGame; //!< Game this menu is used in

    Engine::UIMenu::MenuItem *m_aircraftMenu; //!< Aircraft submenu node
    Engine::UIMenu::MenuItem *m_terrainMenu;  //!< Terrain submenu node
    Engine::UIMenu::MenuItem *m_telemetryOption;
    Engine::UIMenu::MenuItem *m_sticksOption;
  };
}
}

#endif
