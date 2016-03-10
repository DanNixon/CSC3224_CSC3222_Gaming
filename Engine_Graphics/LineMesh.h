/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_LINEMESH_H_
#define _ENGINE_GRAPHICS_LINEMESH_H_

#include "Mesh.h"

namespace Engine
{
  namespace Graphics
  {
    class LineMesh : public Mesh
    {
    public:
      LineMesh(const Engine::Maths::Vector3 &from, const Engine::Maths::Vector3 &to);
      virtual ~LineMesh();

      inline Engine::Maths::Vector3 from() const
      {
        return m_vertices[0];
      }

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