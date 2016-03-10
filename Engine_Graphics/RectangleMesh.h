/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_RectangleMeshMESH_H_
#define _ENGINE_GRAPHICS_RectangleMeshMESH_H_

#include "Mesh.h"

#include <Vector2.h>

namespace Engine
{
namespace Graphics
{
  class RectangleMesh : public Mesh
  {
  public:
    RectangleMesh(const Engine::Maths::Vector2 &dimensions);
    virtual ~RectangleMesh();

    void resize(const Engine::Maths::Vector2 &dimensions);
  };
}
}

#endif