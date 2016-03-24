#pragma once

#include <Game.h>
#include <TopBarMenu.h>

/**
 * @class OptionsMenu
 * @brief Menu used to display simulation options.
 * @auhor Dan Nixon
 */
class OptionsMenu : public Engine::UIMenu::TopBarMenu
{
public:
  OptionsMenu(Engine::Common::Game *game, TTF_Font *font, float textSize = 0.08f);
  virtual ~OptionsMenu();

protected:
  virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);

private:
  Engine::Common::Game *m_game;
};
