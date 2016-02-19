/**
 * @file
 * @author Dan Nixon
 */

#include "Integration.h"

#include <Vector3.h>

void Integration::Euler(Vector3 &out, const Vector3 &x, const Vector3 &y,
                        float dT)
{
  out = x + (y * dT);
}
