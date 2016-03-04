/**
 * @file
 * @author Dan Nixon
 */

#include "InterfaceResolution.h"

#include <Vector2.h>
#include <VectorOperations.h>

#include "PlanarEntity.h"

using namespace Engine::Maths;

namespace Simulation
{
  namespace Physics
  {
    Vector2 InterfaceResolution::InterfaceNormal(Entity &a, Entity &b)
    {
      Vector2 n;

      if (dynamic_cast<const PlanarEntity *>(&a))
        n = -(dynamic_cast<const PlanarEntity *>(&a)->normal());
      else if (dynamic_cast<const PlanarEntity *>(&b))
        n = dynamic_cast<const PlanarEntity *>(&b)->normal();
      else
        n = VectorOperations::GetNormalised(a.position() - b.position());

      return n;
    }

    void InterfaceResolution::Impulse(Entity &a, Entity &b, float epsilon)
    {
      std::cout << "a: " << a << std::endl;
      std::cout << "b: " << b << std::endl;

      Vector2 vAB = a.velocity() + b.velocity();
      Vector2 vN = InterfaceNormal(a, b);

      Vector2 aa = vN * (a.inverseMass() + b.inverseMass());

      float num = -(1 + epsilon) * Vector2::dot(vAB, vN);
      float denom = Vector2::dot(vN, aa);

      float j = abs(num / denom);

      Vector2 vAf = a.velocity() + (vN * j * a.inverseMass());
      Vector2 vBf = b.velocity() - (vN * j * b.inverseMass());

      std::cout << "norm=" << vN << std::endl;
      std::cout << "J=" << j << std::endl;

      std::cout << "vAf=" << vAf << std::endl;
      std::cout << "vBf=" << vBf << std::endl;

      a.setVelocity(vAf);
      b.setVelocity(vBf);
    }
  }
}