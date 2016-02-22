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
  PlanarEntity::PlanarEntity(const Vector2 &pos)
      : Entity(pos)
  {
  }

  PlanarEntity::~PlanarEntity()
  {
  }
}
}