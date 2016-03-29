/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_PHYSICS_CONVEXHULLSHAPE_H_
#define _ENGINE_PHYSICS_CONVEXHULLSHAPE_H_

#include <btBulletDynamicsCommon.h>

#include <Engine_Common/SceneObject.h>

namespace Engine
{
namespace Physics
{
  /**
   * @class ConvesHullShape
   * @brief A wrapper around Bullet's btConvexHullShape that builds the hull from a SceneNode tree.
   * @author Dan Nixon
   *
   * Note that building the initial mesh can be very slow for large trees and detailed meshes.
   */
  class ConvexHullShape : public btConvexHullShape
  {
  public:
    ConvexHullShape();
    virtual ~ConvexHullShape();

    void addSceneTreePoints(Engine::Common::SceneObject *object, size_t maxDepth = std::numeric_limits<size_t>::max(),
                            size_t level = 0);
  };
}
}
#endif