/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_TERRAIN_H_
#define _GAMEDEV_FLIGHTSIM_TERRAIN_H_

#include <Engine_Graphics/RenderableObject.h>

#include <Engine_Physics/Heightmap.h>
#include <Engine_Physics/PhysicalSystem.h>

namespace GameDev
{
namespace FlightSim
{
  /**
   * @class Terrain
   * @brief Class containing all information about a generated terrain.
   * @author Dan Nixon
   */
  class Terrain : public Engine::Graphics::RenderableObject
  {
  public:
    Terrain(const std::string &name, float width, float depth, size_t widthResolution = 1000,
            size_t depthResolution = 1000);
    virtual ~Terrain();

    void init();

    inline void addToSystem(Engine::Physics::PhysicalSystem *system)
    {
      system->addBody(m_physicalBody);
    }

    inline void removeFromSystem(Engine::Physics::PhysicalSystem *system)
    {
      system->removeBody(m_physicalBody);
    }

    inline btCollisionObject *body()
    {
      return m_physicalBody->body();
    }

  protected:
    Engine::Physics::RigidBody *m_physicalBody;     //!< Physical body of the terrain
    Engine::Physics::Heightmap *m_physicsHeightmap; //!< Terrain collision shape
  };
}
}

#endif
