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
    class ConvexHullShape : public btConvexHullShape
    {
    public:
      ConvexHullShape();
      virtual ~ConvexHullShape();

      void addSceneTreePoints(Engine::Common::SceneObject *object, size_t maxDepth = std::numeric_limits<size_t>::max(), size_t level = 0);
    };
  }
}
#endif