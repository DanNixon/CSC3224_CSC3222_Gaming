/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_PHYSICS_BOUNDINGBOXSHAPE_H_
#define _ENGINE_PHYSICS_BOUNDINGBOXSHAPE_H_

#include <btBulletDynamicsCommon.h>

#include <Engine_Common/SceneObject.h>
#include <Engine_Graphics/BoundingBox.h>

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
    Engine::Graphics::BoundingBox<Engine::Maths::Vector3> m_box;
  };
}
}
#endif
