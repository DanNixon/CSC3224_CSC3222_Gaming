/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_SPHERICALMESH_H_
#define _ENGINE_GRAPHICS_SPHERICALMESH_H_

#include "Mesh.h"

namespace Engine
{
namespace Graphics
{
  /**
   * @class SphericalMesh
   * @brief A mesh containing a sphere.
   * @author Dan Nixon
   */
  class SphericalMesh : public Mesh
  {
  public:
    SphericalMesh(float radius = 1.0f, size_t resolution = 64);
    virtual ~SphericalMesh();

    /**
     * @bief Gets the radius of the sphere.
     * @return Radius
     */
    inline float radius() const
    {
      return m_radius;
    }

    void setRadius(float radius);

  private:
    void updateMesh(float radius);

  private:
    const size_t m_resolution; //!< Number of steps in each eaxis
    const float m_deltaTheta;  //!< Theta step
    const float m_deltaPhi;    //!< Phi step
    float m_radius;            //!< Radius of the sphere
  };
}
}

#endif
