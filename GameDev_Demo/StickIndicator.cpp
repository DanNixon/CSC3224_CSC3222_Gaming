/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "StickIndicator.h"

#include <Engine_Graphics/RectangleMesh.h>
#include <Engine_Logging/Logger.h>

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

namespace GameDev
{
namespace Demo
{
  StickIndicator::StickIndicator(const std::string &name, SceneObject * parent)
      : SceneObject(name, parent)
  {
    m_area = new RenderableObject("area", new RectangleMesh(Vector2(2.0f, 2.0f)), ShaderProgramLookup::Instance().get("ui_shader"), nullptr, true);
    m_area->mesh()->setStaticColour(Colour(0.5f, 0.5, 0.5f, 0.5f));
    addChild(m_area);

    m_indicator = new RenderableObject("stick", Mesh::GenerateDisc2D(0.2f), ShaderProgramLookup::Instance().get("ui_shader"), nullptr, true);
    m_indicator->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.0f, -0.1f)));
    m_indicator->mesh()->setStaticColour(Colour(1.0f, 0.0f, 0.0f, 0.8f));
    m_area->addChild(m_indicator);
  }

  StickIndicator::~StickIndicator()
  {
  }

  void StickIndicator::setStickPosition(float horizontal, float vertical)
  {
    m_indicator->setModelMatrix(Matrix4::Translation(Vector3(horizontal, vertical, -0.1f)));
  }
}
}