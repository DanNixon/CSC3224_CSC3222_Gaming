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
    static btTransform ToBullet(const Engine::Maths::Quaternion &quat, const Engine::Maths::Vector3 &vec)
    {
      return btTransform(ToBullet(quat), ToBullet(vec));
    }

    static btVector3 ToBullet(const Engine::Maths::Vector3 &vec)
    {
      return btVector3(vec.x(), vec.y(), vec.z());
    }

    static btQuaternion ToBullet(const Engine::Maths::Quaternion &quat)
    {
      return btQuaternion(quat.i(), quat.j(), quat.k(), quat.w());
    }

    static Engine::Maths::Vector3 FromBullet(const btVector3 &vec)
    {
      return Engine::Maths::Vector3(vec.x(), vec.y(), vec.z());
    }

    static Engine::Maths::Quaternion FromBullet(const btQuaternion &quat)
    {
      return Engine::Maths::Quaternion(quat.w(), quat.x(), quat.y(), quat.z());
    }
  };
}
}
#endif
