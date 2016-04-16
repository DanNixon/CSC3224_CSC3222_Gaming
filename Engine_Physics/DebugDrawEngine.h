/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_PHYSICS_DEBUGDRAWENGINE_H_
#define _ENGINE_PHYSICS_DEBUGDRAWENGINE_H_

#include <btBulletDynamicsCommon.h>

namespace Engine
{
namespace Physics
{
  /**
   * @class DebugDrawEngine
   * @brief
   * @author Dan Nixon
   */
  class DebugDrawEngine : public btIDebugDraw
  {
  public:
    DebugDrawEngine();

    virtual void drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color);
    virtual void drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance,
                                  int lifeTime, const btVector3 &color);
    virtual void draw3dText(const btVector3 &location, const char *textString);

    virtual void reportErrorWarning(const char *warningString);

    virtual void setDebugMode(int debugMode)
    {
      m_debugMode = debugMode;
    }

    virtual int getDebugMode() const
    {
      return m_debugMode;
    }

  private:
    int m_debugMode;
  };
}
}
#endif
