/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_UIMENU_TOPBARMENU_H_
#define _ENGINE_UIMENU_TOPBARMENU_H_

#include "IMenu.h"

namespace Engine
{
  namespace UIMenu
  {
    class TopBarMenu : public IMenu
    {
    public:
      TopBarMenu();
      virtual ~TopBarMenu();
    };
  }
}

#endif