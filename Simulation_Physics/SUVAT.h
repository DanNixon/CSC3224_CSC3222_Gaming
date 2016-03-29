/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_PHYSICS_SUVAT_H_
#define _SIMULATION_PHYSICS_SUVAT_H_

#include <Engine_Maths/Vector3.h>

namespace Simulation
{
namespace Physics
{
  /**
   * @class SUVAT
   * @brief Helper class for performing SUVAT euqations.
   * @author Dan Nixon
   */
  class SUVAT
  {
  public:
    static float getVfromUAT(float u, float a, float t);
    static float getSfromUAT(float u, float a, float t);
    static float getSfromUVT(float u, float v, float t);
    static float getV2fromUAS(float u, float a, float s);
    static float getSfromVTA(float v, float t, float a);

    static Engine::Maths::Vector3 getVfromUAT(const Engine::Maths::Vector3 &u, const Engine::Maths::Vector3 &a,
                                              float &t);
    static Engine::Maths::Vector3 getSfromUAT(const Engine::Maths::Vector3 &u, const Engine::Maths::Vector3 &a,
                                              float &t);
    static Engine::Maths::Vector3 getSfromUVT(const Engine::Maths::Vector3 &u, const Engine::Maths::Vector3 &v,
                                              float &t);
    static Engine::Maths::Vector3 getV2fromUAS(const Engine::Maths::Vector3 &u, const Engine::Maths::Vector3 &a,
                                               const Engine::Maths::Vector3 &s);
    static Engine::Maths::Vector3 getSfromVTA(const Engine::Maths::Vector3 &v, const Engine::Maths::Vector3 &t,
                                              const Engine::Maths::Vector3 &a);
  };
}
}

#endif