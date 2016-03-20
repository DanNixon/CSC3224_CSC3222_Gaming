/**
 * @file
 * @author Dan Nixon
 */

#include "TopBarMenu.h"

#include <Vector3.h>

using namespace Engine::Maths;
using namespace Engine::Graphics;

namespace Engine
{
  namespace UIMenu
  {
    TopBarMenu::TopBarMenu(TTF_Font *font, float height)
      : IMenu(font, height)
      , m_margin(0.05f, 0.02f)
      , m_boxHeight(height)
    {
      setPosition(Vector3(-1.0f, 1.0f - (height + m_margin.y()), 0.0f));
    }

    TopBarMenu::~TopBarMenu()
    {
    }

    void TopBarMenu::layout()
    {
      Vector3 pos(m_margin.x() * 0.5f, 0.0f, 0.0f);

      for (auto it = m_root->children().begin(); it != m_root->children().end(); ++it)
      {
        RenderableObject *obj = dynamic_cast<RenderableObject *>(*it);

        if (obj)
        {
          (*it)->setModelMatrix(Matrix4::Translation(pos));

          Vector3 boxDims = obj->mesh()->boundingBoxDimensions();
          pos[0] += boxDims.x() + m_margin.x();

          layoutChildRecursive(obj, 1);
        }
      }
    }

    void TopBarMenu::layoutChildRecursive(RenderableObject *item, unsigned int level)
    {
      Vector3 pos = Vector3(0.0f, -m_margin.y(), 0.0f);

      if (level > 1)
      {
        Vector3 boxDims = item->mesh()->boundingBoxDimensions();
        pos[0] += boxDims.x() + m_margin.x();
      }
      else
      {
        pos[1] -= m_boxHeight;
      }

      for (auto it = item->children().begin(); it != item->children().end(); ++it)
      {
        RenderableObject *obj = dynamic_cast<RenderableObject *>(*it);

        if (obj)
        {
          (*it)->setModelMatrix(Matrix4::Translation(pos));
          pos[1] -= (m_boxHeight + m_margin.y());

          layoutChildRecursive(obj, level + 1);
        }
      }
    }
  }
}