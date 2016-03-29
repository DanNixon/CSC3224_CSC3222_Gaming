/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_MODELLOADER_H_
#define _ENGINE_GRAPHICS_MODELLOADER_H_

#include <string>

#include <assimp/scene.h>

#include <Engine_Common/SceneObject.h>

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

    Engine::Common::SceneObject *load(const std::string &filename, ShaderProgram *sp);

  private:
    void loadTextures(const struct aiScene *scene, const std::string &directory);
    void loadRecursive(Engine::Common::SceneObject *parent, const struct aiScene *scene, const struct aiNode *node,
                       ShaderProgram *sp);

    Texture **m_textures; //!< Textures for each material
  };
}
}

#endif
