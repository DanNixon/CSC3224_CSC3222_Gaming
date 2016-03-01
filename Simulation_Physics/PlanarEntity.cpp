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
      : Entity(pos, std::numeric_limits<float>::max())
  {
  }

  PlanarEntity::~PlanarEntity()
  {
  }

  /**
   * @brief Gets the normal to the plane.
   * @return Normal
   */
  Vector2 PlanarEntity::normal() const
  {
    Vector2 norm = VectorOperations::GetNormalised(m_position);
    return norm;
  }
}
}
