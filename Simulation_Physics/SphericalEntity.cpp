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
    SphericalEntity::SphericalEntity(const Vector2 & pos)
      : Entity(pos)
    {
    }

    SphericalEntity::~SphericalEntity()
    {
    }
  }
}