/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "SelectionPane.h"

#include <Engine_Graphics/RectangleMesh.h>

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;
using namespace Engine::UIMenu;

namespace Simulation
{
namespace GraphicalPathFinder
{
  /**
   * @copydoc SoupMenu::SoupMenu
   */
  SelectionPane::SelectionPane(Game *game, TTF_Font *font, float textSize, const Vector2 &bgSize)
      : SoupMenu(game, font, textSize)
      , m_pathFinder(static_cast<PathFinder *>(game))
      , m_backgroundColour(Colour(0.5f, 0.5f, 0.5f))
      , m_margin(textSize / 5.0f)
  {
    // Background
    RectangleMesh *backgroundMesh = new RectangleMesh(bgSize);
    backgroundMesh->setAlignment(GetAlignment(Alignment::X_CENTRE, Alignment::Y_BOTTOM));
    RenderableObject *background =
        new RenderableObject("background", backgroundMesh, ShaderProgramLookup::Instance().get("col_shader"));
    background->mesh()->setStaticColour(m_backgroundColour);
    background->setModelMatrix(Matrix4::Translation(Vector3(0.0f, -m_margin, 0.5f)));
    m_root->addChild(background);

    // Previous button
    m_previous = addNewItem(nullptr, "previous", "<<");
    m_previous->setAlignment(GetAlignment(Alignment::Y_BOTTOM, Alignment::X_LEFT));
    m_previous->setModelMatrix(Matrix4::Translation(Vector3(-0.95f, 0.0f) * bgSize * 0.5f));

    // Next button
    m_next = addNewItem(nullptr, "next", ">>");
    m_next->setAlignment(GetAlignment(Alignment::Y_BOTTOM, Alignment::X_RIGHT));
    m_next->setModelMatrix(Matrix4::Translation(Vector3(0.95f, 0.0f) * bgSize * 0.5f));

    // Name text
    m_name = newTextPane("name", GetAlignment(Alignment::Y_BOTTOM, Alignment::X_CENTRE));
    m_name->setText("0: 12345");
  }

  SelectionPane::~SelectionPane()
  {
  }

  TextPane *SelectionPane::newTextPane(const std::string &name, Alignment_bitset alignment)
  {
    TextPane *text =
        new TextPane(name, m_textHeight, ShaderProgramLookup::Instance().get("menu_shader"), m_font, TextMode::SHADED);
    text->setTextColour(Colour(0.0f, 0.0f, 0.0f));
    text->setBackgroundColour(m_backgroundColour);
    text->setAlignment(alignment);
    m_root->addChild(text);
    return text;
  }
}
}
