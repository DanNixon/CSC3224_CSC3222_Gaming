/**
 * @file
 * @author Rich Davison, Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_MESH_H_
#define _ENGINE_GRAPHICS_MESH_H_

#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <SDL/SDL_opengl.h>
#include <assimp/scene.h>

#include <Engine_Common/IMemoryManaged.h>

#include <Engine_Maths/BoundingBox.h>
#include <Engine_Maths/Vector2.h>
#include <Engine_Maths/Vector3.h>
#include <Engine_Maths/Vector4.h>

#include "Colour.h"

using std::ifstream;
using std::string;

namespace Engine
{
namespace Graphics
{
  /**
   * @enum MeshBuffer
   * @brief Describes the type of data held in a buffer.
   */
  enum MeshBuffer
  {
    VERTEX_BUFFER = 0,
    COLOUR_BUFFER = 1,
    TEXTURE_BUFFER,
    NORMAL_BUFFER,
    TANGENT_BUFFER,
    INDEX_BUFFER,
    MAX_BUFFER
  };

  /**
   * @class Mesh
   * @brief Wrapper around OpenGL primitives, geometry and related OGL
   * functions.
   * @author Rich Davison, Dan Nixon
   *
   * Modified from the nclgl library.
   */
  class Mesh : public Engine::Common::IMemoryManaged
  {
  public:
    static Mesh *GenerateDisc2D(float radius, int resolution = 64);
    static Mesh *GenerateRing2D(float radiusOuter, float radiusInner, int resolution = 64);

    static Mesh *LoadMesh(const struct aiMesh *mesh, const struct aiMaterial *material = nullptr);

    Mesh();
    virtual ~Mesh();

    virtual void draw(GLuint program);

    void setStaticColour(const Colour &col);

    /**
     * @brief Gets the upper and lower bounds of the vertices of the mesh.
     * @return Bounding box
     */
    Engine::Maths::BoundingBox3 boundingBox() const
    {
      return m_boundingBox;
    }

    /**
     * @brief Returns the number of vertices that make up this mesh.
     * @return Vertex count
     */
    size_t numVertices() const
    {
      return m_numVertices;
    }

    /**
     * @brief Returns a pointer to the start of the vertex array.
     * @return Vertex array
     */
    Engine::Maths::Vector3 *vertices()
    {
      return m_vertices;
    }

    void bufferData();

  protected:
    bool generateNormals();

    GLuint m_type;                     //!< Type of primitives used in mesh
    GLuint m_arrayObject;              //!< OGL array object for this mesh
    GLuint m_bufferObject[MAX_BUFFER]; //!< OGL buffer objects for each buffer
                                       //!  used in this mesh

    size_t m_numVertices; //!< Number of vertices for the mesh
    size_t m_numIndices;  //!< Number of indices for the mesh

    Engine::Maths::Vector3 *m_vertices;      //!< Pointer to vertex position data
    Colour *m_colours;                       //!< Pointer to vertex colour data
    Engine::Maths::Vector2 *m_textureCoords; //!< Pointer to vertex texture coordinate data
    Engine::Maths::Vector3 *m_normals;       //!< Pointer to vertex normals data
    Engine::Maths::Vector3 *m_tangents;      //!< Pointer to vertex tangents data
    GLuint *m_indices;                       //!< Pointer to vertex indices

    Engine::Maths::BoundingBox3
        m_boundingBox; //!< Bounding box of all vertices (must be set on population of vertex array)

    Colour m_ambientColour;    //!< Colour of scattered ambient light
    Colour m_diffuseColour;    //!< Colour of diffuse scattered light
    Colour m_specularColour;   //!< Colour of specular reflected light
    float m_shininess;         //!< Shininess of the material (specular exponent)
    float m_shininessStrength; //!< Coefficient of specular lighting contribution
  };
}
}

#endif
