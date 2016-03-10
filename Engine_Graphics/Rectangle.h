/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_RECTANGLE_H_
#define _ENGINE_GRAPHICS_RECTANGLE_H_

#include "Mesh.h"

#include <Vector2.h>

namespace Engine
{
  namespace Graphics
  {
    class Rectangle : public Mesh
    {
    public:
      Rectangle(const Engine::Maths::Vector2 &dimensions);
      virtual ~Rectangle();

      void resize(const Engine::Maths::Vector2 &dimensions);
    };
  }
}

#endif