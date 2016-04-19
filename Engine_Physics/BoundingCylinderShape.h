/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_PHYSICS_BOUNDINGCYLINDERSHAPE_H_
#define _ENGINE_PHYSICS_BOUNDINGCYLINDERSHAPE_H_

#include <btBulletDynamicsCommon.h>

#include <Engine_Common/SceneObject.h>
#include <Engine_Maths/BoundingBox.h>

namespace Engine
{
namespace Physics
{
  /**
   * @class BoundingCylinderShape
   * @brief TODO
   * @author Dan Nixon
   */
  class BoundingCylinderShape : public btCylinderShape
  {
  public:
    BoundingCylinderShape();
    virtual ~BoundingCylinderShape();

    void updateDimensionFromSceneTree(Engine::Common::SceneObject *object,
                                      size_t maxDepth = std::numeric_limits<size_t>::max(), size_t level = 0);

    /**
     * @brief Gets the coordinates of the centre of the cylinder.
     * @return Origin coordinates
     */
    inline Engine::Maths::Vector3 origin() const
    {
      return m_box.origin() * m_scaling;
    }

  private:
    Engine::Maths::Vector3 m_scaling;
    Engine::Maths::BoundingBox3 m_box;
  };
}
}
#endif
