/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_UIMENU_IMENU_H_
#define _ENGINE_UIMENU_IMENU_H_

#include <IMemoryManaged.h>

namespace Engine
{
  namespace UIMenu
  {
    class IMenu : public Engine::Common::IMemoryManaged
    {
    public:
      IMenu();
      virtual ~IMenu();
    };
  }
}

#endif