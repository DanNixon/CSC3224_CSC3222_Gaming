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
      , m_margin(0.05f, 0.05f)
    {
      setPosition(Vector3(-1.0f, 1.0f - height, 0.0f));
    }

    TopBarMenu::~TopBarMenu()
    {
    }

    void TopBarMenu::layout()
    {
      Vector3 lastX(0.0f, 0.0f, 0.0f);

      for (auto it = m_root->children().begin(); it != m_root->children().end(); ++it)
      {
        Mesh * m = dynamic_cast<RenderableObject *>(*it)->mesh();

        if (m)
        {
          auto bBox = m->boundingBox();

          Vector3 offset = (bBox.second - bBox.first);
          offset[0] += m_margin.x();

          Vector3 pos = lastX + (offset * 0.5f);

          lastX[0] += offset.x();

          (*it)->setModelMatrix(Matrix4::Translation(pos));
        }
      }
    }
  }
}