/**
 * @file
 * @author Dan Nixon (120263697)
 */

#ifndef _ENGINE_UIMENU_SOUPMENU_H_
#define _ENGINE_UIMENU_SOUPMENU_H_

#include "IMenu.h"

namespace Engine
{
namespace UIMenu
{
  /**
   * @class SoupMenu
   * @brief A menu containing elements intended to be manually positioned.
   * @author Dan Nixon
   */
  class SoupMenu : public IMenu
  {
  public:
    SoupMenu(Engine::Common::Game *game, TTF_Font *font, float textHeight = 0.1f);
    virtual ~SoupMenu();

    virtual void show();

    /**
     * @copydoc IMenu::layout
     */
    virtual void layout()
    {
    }
  };
}
}

#endif
