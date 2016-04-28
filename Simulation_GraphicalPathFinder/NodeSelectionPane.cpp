/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3221 Project 2.
 */

#include "NodeSelectionPane.h"

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
  NodeSelectionPane::NodeSelectionPane(Game *game, TTF_Font *font, float textSize)
      : SoupMenu(game, font, textSize)
      , m_pathFinder(static_cast<PathFinder *>(game))
      , m_margin(textSize / 10.0f)
  {
    Colour backgroundColour(0.5f, 0.5f, 0.5f);

    // Buttons
    MenuItem *previous = addNewItem(nullptr, "previous", "<<");
    previous->setAlignment(GetAlignment(Alignment::Y_CENTRE, Alignment::X_RIGHT));
    previous->setModelMatrix(Matrix4::Translation(Vector3(-m_margin, 2.0f * textSize)));

    MenuItem *next = addNewItem(nullptr, "next", ">>");
    next->setAlignment(GetAlignment(Alignment::Y_CENTRE, Alignment::X_LEFT));
    next->setModelMatrix(Matrix4::Translation(Vector3(m_margin, 2.0f * textSize)));

    MenuItem *pickStart = addNewItem(nullptr, "pick_start", "Pick Start");
    pickStart->setAlignment(GetAlignment(Alignment::Y_CENTRE, Alignment::X_CENTRE));
    pickStart->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.5f * textSize)));

    MenuItem *pickEnd = addNewItem(nullptr, "pick_end", "Pick End");
    pickEnd->setAlignment(GetAlignment(Alignment::Y_CENTRE, Alignment::X_CENTRE));
    pickEnd->setModelMatrix(Matrix4::Translation(Vector3(0.0f, -0.75f * textSize)));

    // Background
    RenderableObject *background = new RenderableObject("background", new RectangleMesh(Vector2(0.3f, 0.3f)),
                                                        ShaderProgramLookup::Instance().get("col_shader"));
    background->mesh()->setStaticColour(backgroundColour);
    background->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.0f, 0.5f)));
    m_root->addChild(background);

    // Node name label
    TextPane *nodeNameLabel =
        new TextPane("node_name", textSize, ShaderProgramLookup::Instance().get("menu_shader"), font, TextMode::SHADED);
    nodeNameLabel->setTextColour(Colour(0.0f, 0.0f, 0.0f));
    nodeNameLabel->setBackgroundColour(backgroundColour);
    nodeNameLabel->setAlignment(GetAlignment(Alignment::Y_CENTRE, Alignment::X_RIGHT));
    nodeNameLabel->setModelMatrix(Matrix4::Translation(Vector3(-m_margin, -2.0f * textSize)));
    nodeNameLabel->setText("Node:");
    m_root->addChild(nodeNameLabel);

    // Node name
    m_nodeName =
        new TextPane("node_name", textSize, ShaderProgramLookup::Instance().get("menu_shader"), font, TextMode::SHADED);
    m_nodeName->setTextColour(Colour(0.0f, 0.0f, 0.0f));
    m_nodeName->setBackgroundColour(backgroundColour);
    m_nodeName->setAlignment(GetAlignment(Alignment::Y_CENTRE, Alignment::X_LEFT));
    m_nodeName->setModelMatrix(Matrix4::Translation(Vector3(m_margin, -2.0f * textSize)));
    m_nodeName->setText("[node]");
    m_root->addChild(m_nodeName);
  }

  NodeSelectionPane::~NodeSelectionPane()
  {
  }

  /**
  * @copydoc IMenu::handleMenuOptionSelection
  */
  void NodeSelectionPane::handleMenuOptionSelection(Engine::UIMenu::MenuItem *item)
  {
    const std::string selectedName(item->name());
    // TODO
  }
}
}
