/**
 * @file
 * @author Dan Nixon
 */

#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "RenderableObject.h"

using namespace Engine::Common;

namespace Engine
{
namespace Graphics
{
  ModelLoader::ModelLoader()
  {
  }

  ModelLoader::~ModelLoader()
  {
  }

  SceneObject *ModelLoader::load(const std::string &filename, ShaderProgram *sp)
  {
    Assimp::Importer i;
    const struct aiScene *scene = i.ReadFile(filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

    if (scene == NULL)
      return NULL;

    SceneObject *obj = new SceneObject(filename);
    loadRecursive(obj, scene, scene->mRootNode, sp);

    return obj;
  }

  void ModelLoader::loadRecursive(SceneObject *sn, const struct aiScene *scene, const struct aiNode *node,
                                  ShaderProgram *sp)
  {
    const aiMatrix4x4 transform = node->mTransformation;

    // Meshes in this node
    for (size_t i = 0; i < node->mNumMeshes; i++)
    {
      const struct aiMesh *m = scene->mMeshes[node->mMeshes[i]];

      if (m->mNumVertices == 0)
        continue;

      Mesh *mesh = Mesh::LoadMesh(m);
      RenderableObject *obj = new RenderableObject("obj", mesh, sp);
      sn->addChild(*obj);
    }

    // Children in this node
    for (size_t i = 0; i < node->mNumChildren; i++)
    {
      SceneObject *child = new SceneObject("child");
      loadRecursive(child, scene, node->mChildren[i], sp);
      sn->addChild(*child);
    }
  }
}
}