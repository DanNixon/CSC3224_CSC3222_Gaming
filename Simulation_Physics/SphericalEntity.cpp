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
  SphericalEntity::SphericalEntity(const Vector2 &pos)
      : Entity(pos)
  {
  }

  SphericalEntity::~SphericalEntity()
  {
  }
}
}
