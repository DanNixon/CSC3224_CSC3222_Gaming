/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "DebugDrawEngine.h"

#include <GL/glew.h>

#include <Engine_Common/MemoryManager.h>
#include <Engine_Graphics/LineMesh.h>
#include <Engine_Logging/Logger.h>

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

namespace Engine
{
namespace Physics
{
  DebugDrawEngine::DebugDrawEngine(Engine::Graphics::ShaderProgram *shader)
      : RenderableObject("debug_draw_engine", nullptr, shader)
      , m_debugMode(0)
  {
  }

  DebugDrawEngine::~DebugDrawEngine()
  {
  }

  void DebugDrawEngine::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
  {
    LineMesh *m =
        new LineMesh(Vector3(from.getX(), from.getY(), from.getZ()), Vector3(to.getX(), to.getY(), to.getZ()));
    m->setStaticColour(Colour(color.getX(), color.getY(), color.getZ(), 1.0f));
    m_meshes.push_back(m);
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

  /**
   * @copydoc RenderableObject::draw
   */
  void DebugDrawEngine::draw(GLuint program)
  {
    for (auto it = m_meshes.begin(); it != m_meshes.end(); ++it)
    {
      (*it)->draw(program);
      MemoryManager::Instance().release(*it);
    }

    m_meshes.clear();
  }
}
}
