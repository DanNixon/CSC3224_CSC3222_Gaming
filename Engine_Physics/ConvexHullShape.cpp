/**
 * @file
 * @author Dan Nixon
 */

#include "ConvexHullShape.h"

#include <Engine_Graphics/RenderableObject.h>

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;

namespace Engine
{
namespace Physics
{
  ConvexHullShape::ConvexHullShape()
  {
  }

  ConvexHullShape::~ConvexHullShape()
  {
  }

  /**
   * @brief Adds the vertices of renderable objects in a scene tree to the
   *        hull.
   * @param object Root node of (sub)tree to add
   * @param maxDepth Maximum recursion depth (defaults to full tree)
   * @param level Current recursion level (do not set manually)
   */
  void ConvexHullShape::addSceneTreePoints(Engine::Common::SceneObject *object, size_t maxDepth, size_t level)
  {
    RenderableObject *rendeable = dynamic_cast<RenderableObject *>(object);
    if (rendeable && rendeable->mesh())
    {
      Vector3 *v = rendeable->mesh()->vertices();
      for (unsigned long i = 0; i < rendeable->mesh()->numVertices(); i++)
      {
        addPoint(btVector3(v->x(), v->y(), v->z()));
        v++;
      }
    }

    if (level > maxDepth)
      return;

    for (SceneObject::SceneObjectListIter it = object->children().begin(); it != object->children().end(); ++it)
    {
      addSceneTreePoints(*it, maxDepth, level + 1);
    }
  }
}
}
