/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_PHYSICS_HEIGHTMAP_H_
#define _ENGINE_PHYSICS_HEIGHTMAP_H_

#include <btBulletCollisionCommon.h>

#include <Engine_ResourceManagment/IMemoryManaged.h>
#include <Engine_Common/SceneObject.h>
#include <Engine_Graphics/HeightmapMesh.h>

namespace Engine
{
namespace Physics
{
  /**
   * @class Heightmap
   * @brief TODO
   * @author Dan Nixon
   */
  class Heightmap : Engine::Common::IMemoryManaged
  {
  public:
    Heightmap();
    virtual ~Heightmap();

    btHeightfieldTerrainShape *shape()
    {
      return m_shape;
    }

    void populate(Engine::Graphics::HeightmapMesh *heightmap);

  private:
    btHeightfieldTerrainShape *m_shape;
  };
}
}
#endif
