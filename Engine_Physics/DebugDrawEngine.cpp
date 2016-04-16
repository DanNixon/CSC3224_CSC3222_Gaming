/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "DebugDrawEngine.h"

#include <GL/glew.h>

#include <Engine_Logging/Logger.h>

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

namespace Engine
{
namespace Physics
{
  DebugDrawEngine::DebugDrawEngine()
      : m_debugMode(0)
  {
  }

  void DebugDrawEngine::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
  {
    glLineWidth(2.5);
    glColor3f(color.getX(), color.getY(), color.getZ());

    glBegin(GL_LINES);

    glVertex3f(from.getX(), from.getY(), from.getZ());
    glVertex3f(to.getX(), to.getY(), to.getZ());

    glEnd();
  }

  void DebugDrawEngine::drawContactPoint(const btVector3 &pointOnB, const btVector3 &normalOnB, btScalar distance,
                                         int lifeTime, const btVector3 &color)
  {
  }

  void DebugDrawEngine::draw3dText(const btVector3 &location, const char *textString)
  {
  }

  void DebugDrawEngine::reportErrorWarning(const char *warningString)
  {
    g_log.warn(std::string(warningString));
  }
}
}
