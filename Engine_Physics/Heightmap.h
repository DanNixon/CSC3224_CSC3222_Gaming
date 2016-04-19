/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_PHYSICS_HEIGHTMAP_H_
#define _ENGINE_PHYSICS_HEIGHTMAP_H_

#include <btBulletCollisionCommon.h>

#include <Engine_Common/SceneObject.h>
#include <Engine_Graphics/HeightmapMesh.h>
#include <Engine_ResourceManagment/IMemoryManaged.h>

namespace Engine
{
namespace Physics
{
  /**
   * @class Heightmap
   * @brief Wrapper around a btHeightfieldTerrainShape for a HeightmapMesh.
   * @author Dan Nixon
   */
  class Heightmap : Engine::ResourceManagment::IMemoryManaged
  {
  public:
    Heightmap();
    virtual ~Heightmap();

    /**
     * @brief Gets the collision shape.
     * @return Pointer to collision shape
     */
    btHeightfieldTerrainShape *shape()
    {
      return m_shape;
    }

    void populate(Engine::Graphics::HeightmapMesh *heightmap);

  private:
    btHeightfieldTerrainShape *m_shape; //!< Collision shape
  };
}
}
#endif
