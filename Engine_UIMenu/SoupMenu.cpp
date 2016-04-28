/**
 * @file
 * @author Dan Nixon (120263697)
 */

#include "SoupMenu.h"

#include <Engine_Maths/Vector3.h>

using namespace Engine::Maths;
using namespace Engine::Graphics;
using namespace Engine::Common;

namespace Engine
{
namespace UIMenu
{
  /**
   * @copydoc IMenu::IMenu
   */
  SoupMenu::SoupMenu(Game *game, TTF_Font *font, float textHeight)
      : IMenu(game, font, textHeight)
  {
  }

  SoupMenu::~SoupMenu()
  {
  }

  /**
   * @copydoc IMenu::show
   */
  void SoupMenu::show()
  {
    m_root->setActive(true);

    // Enable mouse event handling
    enable();
  }
}
}
