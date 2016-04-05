/**
 * @file
 * @author Dan Nixon
 */

#include "InterfaceResolution.h"

#include <Engine_Maths/Vector2.h>
#include <Engine_Maths/VectorOperations.h>

#include "PlanarEntity.h"

using namespace Engine::Maths;

namespace Simulation
{
namespace Physics
{
  /**
   * @brief Resolves an interface using the impulse method.
   * @param interf Interface definition
   * @param epsilon Elasticity coefficient
   */
  void InterfaceResolution::Impulse(InterfaceDef &interf, float epsilon)
  {
    Entity *a = interf.m_e1;
    Entity *b = interf.m_e2;

    Vector2 vAB = a->velocity() + b->velocity();
    Vector2 vN = interf.m_normal;

    Vector2 aa = vN * (a->inverseMass() + b->inverseMass());

    float num = -(1 + epsilon) * Vector2::dot(vAB, vN);
    float denom = Vector2::dot(vN, aa);

    float j = abs(num / denom);

    Vector2 vAf = a->velocity() + (vN * j * a->inverseMass());
    Vector2 vBf = b->velocity() - (vN * j * b->inverseMass());

    a->setVelocity(vAf);
    b->setVelocity(vBf);
  }
}
}
