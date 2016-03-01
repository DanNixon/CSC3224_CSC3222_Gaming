/**
 * @file
 * @author Dan Nixon
 */

#include "InterfaceResolution.h"

#include <Vector2.h>
#include <VectorOperations.h>

using namespace Engine::Maths;

namespace Simulation
{
  namespace Physics
  {
    void InterfaceResolution::Impulse(Entity &a, Entity &b, float epsilon)
    {
      Vector2 vAB = a.velocity() + b.velocity();
      Vector2 vN = VectorOperations::GetNormalised(a.position() - b.position());

      Vector2 aa = vN * (a.inverseMass() + b.inverseMass());

      float num = -(1 + epsilon) * Vector2::dot(vAB, vN);
      float denom = Vector2::dot(vN, aa);

      float j = num / denom;

      Vector2 vAf = a.velocity() + (vN * j * a.inverseMass());
      Vector2 vBf = b.velocity() - (vN * j * b.inverseMass());

      a.setVelocity(vAf);
      b.setVelocity(vBf);
    }
  }
}