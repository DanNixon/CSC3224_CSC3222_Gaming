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
  TextPane::TextPane(float height, ShaderProgram *s, TTF_Font *font)
      : RenderableObject(Mesh::GenerateRect2D(Vector2(height, 1.0f)), s,
                         new Texture())
      , m_height(height)
      , m_font(font)
  {
  }

  TextPane::~TextPane()
  {
  }

  void TextPane::setText(const std::string &str)
  {
    m_texture->text(str, m_font, m_colour);

    Vector2 dim = m_texture->dimensions();
    float ratio = m_height / dim.x();
    dim = dim * ratio;

    m_mesh = Mesh::UpdateRect2D(m_mesh, dim);
  }

  void TextPane::setColour(const Colour &col)
  {
    m_colour = col;
  }
}
}