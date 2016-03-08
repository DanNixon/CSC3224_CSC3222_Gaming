/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_MODELLOADER_H_
#define _ENGINE_GRAPHICS_MODELLOADER_H_

#include <string>

#include <assimp/scene.h>

#include <SceneObject.h>

#include "ShaderProgram.h"

namespace Engine
{
namespace Graphics
{
  class ModelLoader
  {
  public:
    ModelLoader();
    virtual ~ModelLoader();

    Engine::Common::SceneObject *load(const std::string &filename, ShaderProgram *sp);

  private:
    void loadRecursive(Engine::Common::SceneObject *parent, const struct aiScene *scene,
                       const struct aiNode *node, ShaderProgram *sp);
  };
}
}

#endif