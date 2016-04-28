/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "EdgeSelectionPane.h"

#include <Engine_Graphics/RectangleMesh.h>

#include "PathFinder.h"

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
  EdgeSelectionPane::EdgeSelectionPane(Game *game, TTF_Font *font, float textSize)
      : SoupMenu(game, font, textSize)
      , m_pathFinder(static_cast<PathFinder *>(game))
      , m_margin(textSize / 10.0f)
  {
    Colour backgroundColour(0.5f, 0.5f, 0.5f);

    // Background
    RenderableObject *background = new RenderableObject("background", new RectangleMesh(Vector2(0.3f, 0.3f)),
                                                        ShaderProgramLookup::Instance().get("col_shader"));
    background->mesh()->setStaticColour(backgroundColour);
    background->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.0f, 0.5f)));
    m_root->addChild(background);

    // Buttons
    MenuItem *previous = addNewItem(nullptr, "previous", "<<");
    previous->setAlignment(GetAlignment(Alignment::Y_CENTRE, Alignment::X_RIGHT));
    previous->setModelMatrix(Matrix4::Translation(Vector3(-m_margin, 2.0f * textSize)));

    MenuItem *next = addNewItem(nullptr, "next", ">>");
    next->setAlignment(GetAlignment(Alignment::Y_CENTRE, Alignment::X_LEFT));
    next->setModelMatrix(Matrix4::Translation(Vector3(m_margin, 2.0f * textSize)));

    // Connections
    // TODO

    // Weight label
    // TODO

    // Weight
    // TODO

    // Node name label
    TextPane *nodeNameLabel = new TextPane("edge_name_label", textSize,
                                           ShaderProgramLookup::Instance().get("menu_shader"), font, TextMode::SHADED);
    nodeNameLabel->setTextColour(Colour(0.0f, 0.0f, 0.0f));
    nodeNameLabel->setBackgroundColour(backgroundColour);
    nodeNameLabel->setAlignment(GetAlignment(Alignment::Y_CENTRE, Alignment::X_RIGHT));
    nodeNameLabel->setModelMatrix(Matrix4::Translation(Vector3(-m_margin, -2.0f * textSize)));
    nodeNameLabel->setText("Edge:");
    m_root->addChild(nodeNameLabel);

    // Node name
    m_edgeName =
        new TextPane("edge_name", textSize, ShaderProgramLookup::Instance().get("menu_shader"), font, TextMode::SHADED);
    m_edgeName->setTextColour(Colour(0.0f, 0.0f, 0.0f));
    m_edgeName->setBackgroundColour(backgroundColour);
    m_edgeName->setAlignment(GetAlignment(Alignment::Y_CENTRE, Alignment::X_LEFT));
    m_edgeName->setModelMatrix(Matrix4::Translation(Vector3(m_margin, -2.0f * textSize)));
    m_edgeName->setText("[edge]");
    m_root->addChild(m_edgeName);
  }

  EdgeSelectionPane::~EdgeSelectionPane()
  {
  }

  /**
   * @copydoc IMenu::handleMenuOptionSelection
   */
  void EdgeSelectionPane::handleMenuOptionSelection(Engine::UIMenu::MenuItem *item)
  {
    const std::string selectedName(item->name());
    // TODO
  }
}
}
