/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_UIMENU_MENUITEM_H_
#define _ENGINE_UIMENU_MENUITEM_H_

#include <IMemoryManaged.h>

namespace Engine
{
  namespace UIMenu
  {
    class MenuItem : public Engine::Common::IMemoryManaged
    {
    public:
      MenuItem();
      virtual ~MenuItem();
    };
  }
}

#endif