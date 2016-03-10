/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_LINE_H_
#define _ENGINE_GRAPHICS_LINE_H_

#include "Mesh.h"

namespace Engine
{
  namespace Graphics
  {
    class Line : public Mesh
    {
    public:
      Line(const Engine::Maths::Vector3 &from, const Engine::Maths::Vector3 &to);
      virtual ~Line();

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