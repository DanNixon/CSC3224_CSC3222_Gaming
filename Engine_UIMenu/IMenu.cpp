/**
 * @file
 * @author Dan Nixon
 */

#include "IMenu.h"

#include <Matrix4.h>
#include <Shaders.h>

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;

namespace Engine
{
  namespace UIMenu
  {
    IMenu::IMenu(TTF_Font *font, float height)
      : GraphicalScene(new SceneObject("/"),
          Matrix4::BuildViewMatrix(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)),
          Matrix4::Orthographic(0.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f))
      , m_font(font),
      m_textHeight(height)
    {
      // Create shaders
      m_shaderProg = new ShaderProgram();
      m_shaderProg->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
      m_shaderProg->addShader(new FragmentShader("../resources/shader/frag_tex.glsl"));
      m_shaderProg->link();

      // Defualt colours
      m_itemColours[MenuItemState::NORMAL] = Colour(1.0f, 1.0f, 1.0f, 1.0f);
      m_itemColours[MenuItemState::HOVER] = Colour(0.8f, 0.9f, 1.0f, 1.0f);
      m_itemColours[MenuItemState::SELECTED] = Colour(0.5f, 0.8f, 1.0f, 1.0f);
      m_itemColours[MenuItemState::DISABLED] = Colour(0.5f, 0.5f, 0.5f, 1.0f);
    }

    IMenu::~IMenu()
    {
    }

    Vector3 IMenu::position() const
    {
      return m_root->modelMatrix().positionVector();
    }

    void IMenu::setPosition(const Vector3 &position)
    {
      m_root->setModelMatrix(Matrix4::Translation(position));
    }
  }
}