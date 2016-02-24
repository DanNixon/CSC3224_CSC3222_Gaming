/**
* @file
* @author Dan Nixon
*/

#include "PlanarEntity.h"

using namespace Engine::Maths;

namespace Simulation
{
namespace Physics
{
  /**
   * @copydoc Entity::Entity(const Vector2 &)
   * @param direction Indicates direction of the plane (which side entities should be) (-1 or 1)
   *
   * The plane will be offset in axis with non-zero position coordinates.
   */
  PlanarEntity::PlanarEntity(const Vector2 &pos, int direction)
      : Entity(pos)
      , m_direction(direction)
  {
    if (!(direction == -1 || direction == 1))
      throw std::runtime_error("Direction must be either -1 or 1");
  }

  PlanarEntity::~PlanarEntity()
  {
  }

  int PlanarEntity::axis() const
  {
    int retVal = -1;

    for (int i = 0; i < 2; i++)
    {
      if (m_position[i] != 0.0f)
        retVal = i;
    }

    return retVal;
  }
}
}
