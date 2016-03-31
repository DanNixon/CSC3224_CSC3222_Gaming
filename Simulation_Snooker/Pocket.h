/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_SNOOKER_POCKET_H_
#define _SIMULATION_SNOOKER_POCKET_H_

#include <Engine_Graphics/RenderableObject.h>
#include <Engine_Maths/Vector4.h>

#include <Simulation_Physics/SphericalEntity.h>

// TODO: this should not be a RenderableObject, that was only for debugging

namespace Simulation
{
namespace Snooker
{
  /**
   * @class Pocket
   * @brief Represents a snooker pocket.
   * @author Dan Nixon
   */
  class Pocket : public Simulation::Physics::SphericalEntity, public Engine::Graphics::RenderableObject
  {
  public:
    static const float RADIUS;

    Pocket(const Engine::Maths::Vector2 &pos);
    virtual ~Pocket();

    // TODO
    virtual void setPosition(const Engine::Maths::Vector2 &pos);
  };
}
}

#endif
