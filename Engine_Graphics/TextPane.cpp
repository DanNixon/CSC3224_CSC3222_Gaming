/**
 * @file
 * @author Dan Nixon
 */

#include "TextPane.h"

using namespace Engine::Maths;

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Creates a new text pane.
   * @param height Height of the text
   * @param s Shader used to render text
   * @param font Text font
   */
  TextPane::TextPane(const std::string &name, float height, ShaderProgram *s,
                     TTF_Font *font)
      : RenderableObject(name, Mesh::GenerateRect2D(Vector2(height, 1.0f)), s,
                         new Texture())
      , m_height(height)
      , m_font(font)
  {
  }

  TextPane::~TextPane()
  {
  }

  /**
   * @brief Sets the displayed text.
   * @param str Text
   */
  void TextPane::setText(const std::string &str)
  {
    m_texture->text(str, m_font, m_colour);

    Vector2 dim = m_texture->dimensions();
    float ratio = m_height / dim.y();
    dim = dim * ratio;

    m_mesh = Mesh::UpdateRect2D(m_mesh, dim);
  }

  /**
   * @brief Sets the colour fo the text,
   * @param col Text colour
   */
  void TextPane::setColour(const Colour &col)
  {
    m_colour = col;
  }
}
}
