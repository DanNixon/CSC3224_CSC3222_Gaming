/**
* @file
* @author Dan Nixon
*/

#include "PlanarEntity.h"

#include <VectorOperations.h>

using namespace Engine::Maths;

namespace Simulation
{
namespace Physics
{
  /**
   * @copydoc Entity::Entity(const Vector2 &)
   */
  PlanarEntity::PlanarEntity(const Vector2 &pos)
      : Entity(pos, 1.0f, true)
  {
    facing();
  }

  PlanarEntity::~PlanarEntity()
  {
  }

  void PlanarEntity::facing(const Vector2 &p)
  {
    m_normal = VectorOperations::GetNormalised(p - m_position);
  }

  /**
   * @brief Gets the normal to the plane.
   * @return Normal
   */
  Vector2 PlanarEntity::normal() const
  {
    return m_normal;
  }
}
}
