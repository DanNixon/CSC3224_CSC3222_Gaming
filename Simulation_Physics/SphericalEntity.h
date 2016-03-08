/**
* @file
* @author Dan Nixon
*/

#ifndef _SIMULATION_PHYSICS_SPHERICALENTITY_H_
#define _SIMULATION_PHYSICS_SPHERICALENTITY_H_

#include "Entity.h"

namespace Simulation
{
namespace Physics
{
  /**
   * @class SphericalEntity
   * @brief Represents an entity in a 2D circle.
   * @author Dan Nixon
   */
  class SphericalEntity : public Entity
  {
  public:
    SphericalEntity(const Engine::Maths::Vector2 &pos, float mass, float radius,
                    bool stationary = false, float dragCoeff = 1.0f, float velocityFloor = 0.0f,
                    float impactDistance = 0.0f);
    virtual ~SphericalEntity();

    float radius() const;
    float radius2() const;

    void setRadius(float radius);

    float impactDistance() const;

  private:
    float m_radius2;        //!< Radius squared
    float m_impactDistance; //!< The distance the entity can travel into another
                            //! spherebefore a collision is reported
  };
}
}

#endif