/**
 * @file
 * @author Dan Nixon
 */

#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>

#include <StringUtils.h>

#include "Mesh.h"
#include "RenderableObject.h"

using namespace Engine::Common;
using namespace Engine::Utility;

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

  /**
   * @brief Load a 3D model into a tree of SceneObject.
   * @param filename File to load
   * @param sp Shader to assign to new RenderableObject
   * @return SceneObject tree
   */
  SceneObject *ModelLoader::load(const std::string &filename, ShaderProgram *sp)
  {
    Assimp::Importer i;
    const struct aiScene *scene = i.ReadFile(filename.c_str(),
      aiProcess_CalcTangentSpace |
      aiProcess_Triangulate |
      aiProcess_JoinIdenticalVertices |
      aiProcess_SortByPType |
      aiProcess_GenUVCoords |
      aiProcess_TransformUVCoords );

    if (scene == NULL)
      return NULL;

    SceneObject *obj = new SceneObject(filename);
    std::string directory = StringUtils::DirectoryFromPath(filename);
    ;

    loadTextures(scene, directory);
    loadRecursive(obj, scene, scene->mRootNode, sp);

    return obj;
  }

  /**
   * @brief Loads textures for each material used in the model.
   * @param scene Assimp scene being loaded
   * @param directory DIrectory in which textures are stored
   */
  void ModelLoader::loadTextures(const struct aiScene *scene, const std::string &directory)
  {
    m_textures = new Texture *[scene->mNumMaterials];
    for (size_t i = 0; i < scene->mNumMaterials; i++)
    {
      const aiMaterial *material = scene->mMaterials[i];

      m_textures[i] = NULL;
      if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
      {
        aiString path;

        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
        {
          std::string filename = directory + "/" + path.data;
          m_textures[i] = new Texture();
          m_textures[i]->load(filename);

          if (!m_textures[i]->valid())
          {
            std::cerr << "Failed to load testure \"" << filename << "\", for material " << material << std::endl;
            m_textures[i] = NULL;
          }
        }
      }
    }
  }

  /**
   * @brief Load a node of the scene tree.
   * @param sn SceneObject node
   * @param scene Assimp scene
   * @param node Assimp scene node
   * @param sp Shader to assign to new RenderableObject
   */
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

      size_t matIdx = m->mMaterialIndex;
      const struct aiMaterial *mat = scene->mMaterials[matIdx];

      Mesh *mesh = Mesh::LoadMesh(m, mat);
      RenderableObject *obj = new RenderableObject("obj", mesh, sp, m_textures[matIdx]);
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
