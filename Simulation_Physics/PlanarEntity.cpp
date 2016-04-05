/**
* @file
* @author Dan Nixon
*/

#include "PlanarEntity.h"

#include <Engine_Maths/VectorOperations.h>

using namespace Engine::Maths;
using namespace Engine::Graphics;

namespace Simulation
{
namespace Physics
{
  /**
   * @copydoc Entity::Entity(const Vector2 &)
   */
  PlanarEntity::PlanarEntity(const Vector2 &pos)
      : Entity(pos, std::numeric_limits<float>::max(), true)
  {
    facing();

    // TODO: cases where plane is flat give a reduced box
    m_originBox = BoundingBox<Vector2>();
  }

  PlanarEntity::~PlanarEntity()
  {
  }

  /**
   * @brief Sets the direction the plane is facing.
   * @param p Point the plane is facing
   */
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