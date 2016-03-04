/**
* @file
* @author Dan Nixon
*/

#ifndef _SIMULATION_PHYSICS_PLANARENTITY_H_
#define _SIMULATION_PHYSICS_PLANARENTITY_H_

#include "Entity.h"

namespace Simulation
{
namespace Physics
{
  /**
   * @class PlanarEntity
   * @brief Represents an entity that exists in any orientation.
   * @author Dan Nixon
   */
  class PlanarEntity : public Entity
  {
  public:
    PlanarEntity(const Engine::Maths::Vector2 &pos);
    virtual ~PlanarEntity();

    void facing(const Engine::Maths::Vector2 &p = Engine::Maths::Vector2(0.0f,
                                                                         0.0f));

    Engine::Maths::Vector2 normal() const;

  private:
    Engine::Maths::Vector2 m_normal; //!< Plane normal
  };
}
}

#endif
