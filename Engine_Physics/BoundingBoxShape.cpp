/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "BoundingBoxShape.h"

#include <Engine_Graphics/RenderableObject.h>

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;

namespace Engine
{
namespace Physics
{
  BoundingBoxShape::BoundingBoxShape()
      : btBoxShape(btVector3())
  {
  }

  BoundingBoxShape::~BoundingBoxShape()
  {
  }

  /**
   * @brief Updates the size of the bounding box to contain all meshes in a
   *        scene (sub)tree.
   * @param object Root node of (sub)tree to add
   * @param maxDepth Maximum recursion depth (defaults to full tree)
   * @param level Current recursion level (do not set manually)
   */
  void BoundingBoxShape::updateDimensionFromSceneTree(SceneObject *object, size_t maxDepth, size_t level)
  {
    RenderableObject *rendeable = dynamic_cast<RenderableObject *>(object);
    if (rendeable && rendeable->mesh())
      m_box.resizeByBoundingBox(rendeable->mesh()->boundingBox());

    if (level > maxDepth)
      return;

    for (SceneObject::SceneObjectListIter it = object->children().begin(); it != object->children().end(); ++it)
    {
      updateDimensionFromSceneTree(*it, maxDepth, level + 1);
    }

    // Update the box shape
    if (level == 0)
    {
      Vector3 boxDims = m_box.longestBoundDistance();
      btVector3 boxHalfExtents(boxDims.x(), boxDims.y(), boxDims.z());

      setSafeMargin(boxHalfExtents);
      btVector3 margin(getMargin(), getMargin(), getMargin());
      m_implicitShapeDimensions = (boxHalfExtents * m_localScaling) - margin;
    }
  }
}
}
