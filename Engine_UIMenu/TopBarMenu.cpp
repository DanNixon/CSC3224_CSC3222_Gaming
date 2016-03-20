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
      setPosition(Vector3(-1.0f, 1.0f - height - m_margin.y(), 0.0f));
    }

    TopBarMenu::~TopBarMenu()
    {
    }

    void TopBarMenu::layout()
    {
      Vector3 nextPos(m_margin.x() * 0.5f, m_textHeight * 0.5f, 0.0f);

      for (auto it = m_root->children().begin(); it != m_root->children().end(); ++it)
      {
        Mesh * m = dynamic_cast<RenderableObject *>(*it)->mesh();

        if (m)
        {
          (*it)->setModelMatrix(Matrix4::Translation(nextPos));

          auto bBox = m->boundingBox();
          Vector3 boxDims = (bBox.second - bBox.first);
          nextPos[0] += boxDims.x() + m_margin.x();
        }
      }
    }
  }
}