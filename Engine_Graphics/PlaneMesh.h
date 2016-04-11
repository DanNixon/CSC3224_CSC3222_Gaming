/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_PLANEMESH_H_
#define _ENGINE_GRAPHICS_PLANEMESH_H_

#include "Mesh.h"

#include <Engine_Maths/Vector3.h>

namespace Engine
{
namespace Graphics
{
  /**
   * @class PlaneMesh
   * @brief A mesh containing a finite rectangle in a plane.
   * @author Dan Nixon
   */
  class PlaneMesh : public Mesh
  {
  public:
    PlaneMesh(char axis, float size = 1000000.0f);
    virtual ~PlaneMesh();

  private:
    void resize();
  };
}
}

#endif
