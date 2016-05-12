/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "Terrain.h"

#include <Engine_Graphics/HeightmapMesh.h>
#include <Engine_Graphics/Texture.h>
#include <Engine_Logging/Logger.h>

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;
using namespace Engine::Physics;

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

namespace GameDev
{
namespace FlightSim
{
  /**
   * @brief Creates a new terrain.
   * @param name Name of the terrain
   */
  Terrain::Terrain(const std::string &name)
      : RenderableObject(name, nullptr, ShaderProgramLookup::Instance().get("terrain_shader"),
                         TextureLookup::Instance().get("terrain_texture"))
  {
  }

  Terrain::~Terrain()
  {
  }

  /**
   * @brief Initialise the terrain.
   * @param width Width in m
   * @param depth Depth in m
   * @param widthResolution Number of steps in width
   * @param depthResolution Number of steps in depth
   * @param heightData Pointer to array of height data
   */
  void Terrain::init(float width, float depth, size_t widthResolution, size_t depthResolution, float *heightData)
  {
    // Mesh
    m_mesh = new HeightmapMesh(widthResolution, depthResolution, width, depth);
    static_cast<HeightmapMesh *>(m_mesh)->setHeight(heightData);

    // Heightmap collision shape
    m_physicsHeightmap = new Heightmap();
    m_physicsHeightmap->populate(static_cast<HeightmapMesh *>(m_mesh));

    // Motion
    SceneObjectMotionState *motion = new SceneObjectMotionState(this, Vector3(), Quaternion());

    // Body
    m_physicalBody = new RigidBody(motion, 0.0f, btVector3(0.0f, 0.0f, 0.0f), m_physicsHeightmap->shape());
    m_physicalBody->body()->setActivationState(DISABLE_DEACTIVATION);
  }
}
}
