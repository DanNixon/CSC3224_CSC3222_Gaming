/**
* @file
* @author Dan Nixon
*/

#include "Cushion.h"

using namespace Engine::Maths;

namespace Simulation
{
namespace Snooker
{
  /**
   * @copydoc PlanarEntity::PlanarEntity(const Vector 2 &)
   */
  Cushion::Cushion(const Vector2 &pos)
      : PlanarEntity(pos)
  {
  }

  Cushion::~Cushion()
  {
  }
}
}