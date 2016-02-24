/**
* @file
* @author Dan Nixon
*/

#include "Cushion.h"

using namespace Engine::Maths;

/**
 * @copydoc PlanarEntity::PlanarEntity(const Vector 2 &)
 */
Cushion::Cushion(const Vector2 &pos, int direction)
    : PlanarEntity(pos, direction)
{
}

Cushion::~Cushion()
{
}
