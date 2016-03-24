#pragma once

#include <TopBarMenu.h>
#include <Game.h>

class OptionsMenu : public Engine::UIMenu::TopBarMenu
{
public:
  OptionsMenu(TTF_Font * font, Engine::Common::Game * game, float textSize = 0.08f);
  virtual ~OptionsMenu();

protected:
  virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);

private:
  Engine::Common::Game * m_game;
};