/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "TextPane.h"

#include "RectangleMesh.h"

using namespace Engine::Maths;

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Creates a new text pane.
   * @param name Name of the text pane
   * @param height Height of the text
   * @param s Shader used to render text
   * @param font Text font
   * @param mode Text rendering mode
   */
  TextPane::TextPane(const std::string &name, float height, ShaderProgram *s, TTF_Font *font, TextMode mode)
      : RenderableObject(name, new RectangleMesh(Vector2(height, 1.0f)), s, new Texture())
      , m_height(height)
      , m_font(font)
      , m_mode(mode)
      , m_fgColour()
      , m_bgColour(0.0f, 0.0f, 0.0f, 1.0f)
  {
  }

  TextPane::~TextPane()
  {
  }

  /**
   * @copydoc RectangleMesh::setAlignment
   */
  void TextPane::setAlignment(Alignment_bitset alignment)
  {
    static_cast<RectangleMesh *>(m_mesh)->setAlignment(alignment);
    redraw();
  }

  /**
   * @brief Sets the displayed text.
   * @param str Text
   */
  void TextPane::setText(const std::string &str)
  {
    m_text = str;
    redraw();
  }

  /**
   * @brief Sets the colour of the text.
   * @param col Text colour
   */
  void TextPane::setTextColour(const Colour &col)
  {
    m_fgColour = col;
    redraw();
  }

  /**
   * @brief Sets the colour of the text background.
   * @param col Background colour
   */
  void TextPane::setBackgroundColour(const Colour &col)
  {
    m_bgColour = col;
    redraw();
  }

  /**
   * @brief Updates the text pane by redrawing the texture.
   */
  void TextPane::redraw()
  {
    size_t numLines = m_texture->text(m_text, m_font, m_fgColour, m_mode, m_bgColour);

    Vector2 dim = m_texture->dimensions();
    float ratio = (m_height * numLines) / dim.y();
    dim = dim * ratio;

    static_cast<RectangleMesh *>(m_mesh)->setDimensions(dim);
  }
}
}
