/**
 * @file
 * @author Dan Nixon
 */

#include "OptionsMenu.h"

using namespace Engine::Common;
using namespace Engine::UIMenu;

namespace GameDev
{
namespace Demo
{
  OptionsMenu::OptionsMenu(Game *game, TTF_Font *font, float textSize)
      : TopBarMenu(game, font, textSize)
      , m_game(game)
  {
  }

  OptionsMenu::~OptionsMenu()
  {
  }

  void OptionsMenu::handleMenuOptionSelection(Engine::UIMenu::MenuItem *item)
  {
    if (item->name() == "exit")
      m_game->exit();

    // TODO
  }
}
}