/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_PHYSICS_BOUNDINGBOXSHAPE_H_
#define _ENGINE_PHYSICS_BOUNDINGBOXSHAPE_H_

#include <btBulletDynamicsCommon.h>

#include <Engine_Common/SceneObject.h>
#include <Engine_Maths/BoundingBox.h>

namespace Engine
{
namespace Physics
{
  /**
   * @class BoundingBoxShape
   * @brief A wrapper around Bullet's btBoxShape that builds the bounding box
   *        from a SceneNode tree.
   * @author Dan Nixon
   */
  class BoundingBoxShape : public btBoxShape
  {
  public:
    BoundingBoxShape();
    virtual ~BoundingBoxShape();

    void updateDimensionFromSceneTree(Engine::Common::SceneObject *object,
                                      size_t maxDepth = std::numeric_limits<size_t>::max(), size_t level = 0);

  private:
    Engine::Maths::BoundingBox3 m_box;
  };
}
}
#endif
