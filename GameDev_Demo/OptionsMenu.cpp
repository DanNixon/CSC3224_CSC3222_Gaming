#include "OptionsMenu.h"

using namespace Engine::Common;
using namespace Engine::UIMenu;

OptionsMenu::OptionsMenu(TTF_Font * font, Game * game, float textSize)
  : TopBarMenu(font, game->windowX(), game->windowY(), textSize)
  , m_game(game)
{
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::handleMenuOptionSelection(Engine::UIMenu::MenuItem *item)
{
  if (item->name() == "Exit")
    m_game->exit();

  // TODO
}