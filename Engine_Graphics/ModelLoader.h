/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_MODELLOADER_H_
#define _ENGINE_GRAPHICS_MODELLOADER_H_

#include <string>

#include <assimp/scene.h>

#include "RenderableObject.h"
#include "ShaderProgram.h"
#include "Texture.h"

namespace Engine
{
namespace Graphics
{
  /**
   * @class ModelLoader
   * @brief Loader for 3D models (supported by Assimp).
   * @author Dan Nixon
   */
  class ModelLoader
  {
  public:
    ModelLoader();
    virtual ~ModelLoader();

    Engine::Graphics::RenderableObject *load(const std::string &filename, ShaderProgram *sp);

  private:
    void loadTextures(const struct aiScene *scene, const std::string &directory);
    void loadRecursive(Engine::Graphics::RenderableObject *parent, const struct aiScene *scene,
                       const struct aiNode *node, ShaderProgram *sp);

    Texture **m_textures; //!< Textures for each material
  };
}
}

#endif
