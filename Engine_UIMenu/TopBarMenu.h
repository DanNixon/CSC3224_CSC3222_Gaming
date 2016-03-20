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
      TopBarMenu(TTF_Font *font, float height = 1.0f);
      virtual ~TopBarMenu();

      inline Engine::Maths::Vector2 margin() const
      {
        return m_margin;
      }

      void setMargin(const Engine::Maths::Vector2 &margin)
      {
        m_margin = margin;
      }

      virtual void layout();

    private:
      Engine::Maths::Vector2 m_margin;
    };
  }
}

#endif