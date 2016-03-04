/**
 * @file
 * @author Rich Davison, Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_MESH_H_
#define _ENGINE_GRAPHICS_MESH_H_

#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <SDL/SDL_opengl.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

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
  class Mesh
  {
  public:
    static Mesh *GenerateTriangle();
    static Mesh *GenerateLine(const Engine::Maths::Vector3 &from,
                              const Engine::Maths::Vector3 &to);
    static Mesh *GenerateDisc2D(float radius, int resolution = 64);
    static Mesh *GenerateRing2D(float radiusOuter, float radiusInner,
                                int resolution = 64);
    static Mesh *GenerateRect2D(const Engine::Maths::Vector2 &dimensions);
    static Mesh *LoadASCIIMeshFile(const string &filename);
    static Mesh *LoadModelFile(const string &filename, size_t meshIdx);

    static std::pair<Engine::Maths::Vector3, Engine::Maths::Vector3>
    GetBoundingBox(Mesh *m);

    Mesh();
    virtual ~Mesh();

    virtual void draw();

    void setStaticColour(const Engine::Maths::Vector4 &col);

  protected:
    bool generateNormals();
    void bufferData();

    GLuint m_type;                     //!< Type of primitives used in mesh
    GLuint m_arrayObject;              //!< OGL array object for this mesh
    GLuint m_bufferObject[MAX_BUFFER]; //!< OGL buffer objects for each buffer
                                       //!  used in this mesh
    GLuint m_numVertices;              //!< Number of vertices for the mesh
    GLuint m_numIndices;               //!< Number of indices for the mesh

    Engine::Maths::Vector3 *m_vertices; //!< Pointer to vertex position data
    Engine::Maths::Vector4 *m_colours;  //!< Pointer to vertex colour data
    Engine::Maths::Vector2 *
        m_textureCoords; //!< Pointer to vertex texture coordinate data
    Engine::Maths::Vector3 *m_normals;  //!< Pointer to vertex normals data
    Engine::Maths::Vector3 *m_tangents; //!< Pointer to vertex tangents data
    size_t *m_indices;                  //!< Pointer to vertex indices data
  };
}
}

#endif