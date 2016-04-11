/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_LINEMESH_H_
#define _ENGINE_GRAPHICS_LINEMESH_H_

#include "Mesh.h"

namespace Engine
{
namespace Graphics
{
  /**
   * @class LineMesh
   * @brief A mesh containing a single zero width line.
   * @author Dan Nixon
   */
  class LineMesh : public Mesh
  {
  public:
    LineMesh(const Engine::Maths::Vector3 &from, const Engine::Maths::Vector3 &to);
    virtual ~LineMesh();

    /**
     * @brief Get starting point of the line
     * @return Starting point
     */
    inline Engine::Maths::Vector3 from() const
    {
      return m_vertices[0];
    }

    /**
     * @brief Get finishing point of the line
     * @return Finishing point
     */
    inline Engine::Maths::Vector3 to() const
    {
      return m_vertices[1];
    }

    void setFrom(const Engine::Maths::Vector3 &from);
    void setTo(const Engine::Maths::Vector3 &to);

  private:
    void updateMesh(const Engine::Maths::Vector3 &from, const Engine::Maths::Vector3 &to);
  };
}
}

#endif
