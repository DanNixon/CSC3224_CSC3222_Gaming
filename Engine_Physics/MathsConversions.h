/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_PHYSICS_MATHSCONVERSIONS_H_
#define _ENGINE_PHYSICS_MATHSCONVERSIONS_H_

#include <btBulletDynamicsCommon.h>

#include <Engine_Maths/Quaternion.h>
#include <Engine_Maths/Vector3.h>

namespace Engine
{
namespace Physics
{
  /**
   * @class MathsConversions
   * @brief Functions for converting between Bullet math types and the engines
   *        math types.
   * @author Dan Nixon
   */
  class MathsConversions
  {
  public:
    /**
     * @brief Converts to a Bullet physics btTransform.
     * @param quat Quaternion
     * @param vec Transformation
     * @return Bullet transform
     */
    static btTransform ToBullet(const Engine::Maths::Quaternion &quat, const Engine::Maths::Vector3 &vec)
    {
      return btTransform(ToBullet(quat), ToBullet(vec));
    }

    /**
     * @brief Converts to a Bullet physics btVector3.
     * @param vec Vector
     * @return Bullet vector
     */
    static btVector3 ToBullet(const Engine::Maths::Vector3 &vec)
    {
      return btVector3(vec.x(), vec.y(), vec.z());
    }

    /**
     * @brief Converts to a Bullet physics btQuaternion.
     * @param quat Quaternion
     * @return Bullet quaternion
     */
    static btQuaternion ToBullet(const Engine::Maths::Quaternion &quat)
    {
      return btQuaternion(quat.i(), quat.j(), quat.k(), quat.w());
    }

    /**
     * @brief Converts from a Bullet physics btVector3.
     * @param vec Bullet vector
     * @return Vector
     */
    static Engine::Maths::Vector3 FromBullet(const btVector3 &vec)
    {
      return Engine::Maths::Vector3(vec.x(), vec.y(), vec.z());
    }

    /**
     * @brief Converts from a Bullet physics btQuaternion.
     * @param quat Bullet quaternion
     * @return Quaternion
     */
    static Engine::Maths::Quaternion FromBullet(const btQuaternion &quat)
    {
      return Engine::Maths::Quaternion(quat.w(), quat.x(), quat.y(), quat.z());
    }
  };
}
}
#endif
