/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
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
namespace FlightSim
{
  /**
   * @brief Creates a new stick indicator.
   * @param name Name of the indicator
   * @param parent Parent scene object
   */
  StickIndicator::StickIndicator(const std::string &name, SceneObject *parent)
      : SceneObject(name, parent)
  {
    // Background rectangle
    m_background = new RenderableObject("area", new RectangleMesh(Vector2(2.0f, 2.0f)),
                                        ShaderProgramLookup::Instance().get("ui_shader"), nullptr, true);
    m_background->mesh()->setStaticColour(Colour(0.5f, 0.5, 0.5f, 0.5f));
    addChild(m_background);

    // Stick position indicator
    m_indicator = new RenderableObject("stick", Mesh::GenerateDisc2D(0.2f),
                                       ShaderProgramLookup::Instance().get("ui_shader"), nullptr, true);
    m_indicator->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.0f, -0.1f)));
    m_indicator->mesh()->setStaticColour(Colour(1.0f, 0.0f, 0.0f, 0.8f));
    m_background->addChild(m_indicator);
  }

  StickIndicator::~StickIndicator()
  {
  }

  /**
   * @brief Sets the positions of the stick indicator.
   * @param horizontal Horizontal stick position
   * @param vertical Vertical stick position
   *
   * Both positions are in interval [-1,1].
   */
  void StickIndicator::setStickPosition(float horizontal, float vertical)
  {
    m_indicator->setModelMatrix(Matrix4::Translation(Vector3(horizontal, vertical, -0.1f)));
  }
}
}
