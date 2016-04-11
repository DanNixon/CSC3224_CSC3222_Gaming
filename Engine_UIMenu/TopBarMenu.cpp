/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "TopBarMenu.h"

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
  TopBarMenu::TopBarMenu(Game *game, TTF_Font *font, float textHeight)
      : IMenu(game, font, textHeight)
      , m_margin(0.01f, 0.01f)
  {
    Vector2 dMargin = m_margin * 2.0f;
    setPosition(Vector3(-1.0f + dMargin.x(), 1.0f - textHeight - dMargin.y(), 0.0f));
  }

  TopBarMenu::~TopBarMenu()
  {
  }

  /**
   * @copydoc IMenu::layout
   */
  void TopBarMenu::layout()
  {
    Vector3 pos;

    for (auto it = m_root->children().begin(); it != m_root->children().end(); ++it)
    {
      RenderableObject *obj = dynamic_cast<RenderableObject *>(*it);

      if (obj)
      {
        (*it)->setModelMatrix(Matrix4::Translation(pos));

        Vector3 boxDims = obj->mesh()->boundingBox().size();
        pos[0] += boxDims.x() + m_margin.x();

        layoutChildRecursive(obj, 1);
      }
    }
  }

  /**
   * @copydoc IMenu::show
   */
  void TopBarMenu::show()
  {
    m_root->setActive(true, 1);

    // Enable mouse event handling
    enable();
  }

  /**
   * @brief Performs layout for a given node in the item tree.
   * @param item Node to layout children of
   * @param level Level in the item tree (0 = root node)
   */
  void TopBarMenu::layoutChildRecursive(RenderableObject *item, unsigned int level)
  {
    Vector3 pos = Vector3(0.0f, -m_margin.y(), 0.0f);

    if (level > 1)
    {
      Vector3 boxDims = item->mesh()->boundingBox().size();
      pos[0] += boxDims.x() + m_margin.x();
    }
    else
    {
      pos[1] -= m_textHeight;
    }

    for (auto it = item->children().begin(); it != item->children().end(); ++it)
    {
      RenderableObject *obj = dynamic_cast<RenderableObject *>(*it);

      if (obj)
      {
        (*it)->setModelMatrix(Matrix4::Translation(pos));
        pos[1] -= (m_textHeight + m_margin.y());

        layoutChildRecursive(obj, level + 1);
      }
    }
  }
}
}
