/**
* @file
* @author Dan Nixon
*/

#include "SphericalEntity.h"

using namespace Engine::Maths;

namespace Simulation
{
namespace Physics
{
  /**
   * @copydoc Entity::Entity(const Vector 2 &)
   */
  SphericalEntity::SphericalEntity(const Engine::Maths::Vector2 &pos,
                                   float mass,
                                   float radius, bool stationary,
                                   float dragCoeff, float velocityFloor)
      : Entity(pos, mass, stationary, dragCoeff, velocityFloor)
      , m_radius2(radius * radius)
  {
  }

  SphericalEntity::~SphericalEntity()
  {
  }

  /**
   * @brief Gets the radius of the entity.
   * @return Radius
   */
  float SphericalEntity::radius() const
  {
    return sqrt(m_radius2);
  }

  /**
   * @brief Gets the squared radius of the entity.
   * @return Radius squared
   */
  float SphericalEntity::radius2() const
  {
    return m_radius2;
  }

  /**
   * @brief Sets the radius of the entity.
   * @param radius Radius
   */
  void SphericalEntity::setRadius(float radius)
  {
    m_radius2 = radius * radius;
  }
}
}
