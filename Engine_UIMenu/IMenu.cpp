/**
 * @file
 * @author Dan Nixon
 */

#include "IMenu.h"

#include <Engine_Common/Game.h>
#include <Engine_Graphics/Shaders.h>
#include <Engine_Maths/Matrix4.h>

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;

namespace Engine
{
namespace UIMenu
{
  /**
   * @brief Creates a new menu.
   * @param game Game instance menu is used in
   * @param font Font to render text with
   * @param textHeight Height of the text
   */
  IMenu::IMenu(Game *game, TTF_Font *font, float textHeight)
      : GraphicalScene(new SceneObject("/"),
                       Matrix4::BuildViewMatrix(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)),
                       Matrix4::Orthographic(0.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f))
      , m_game(game)
      , m_font(font)
      , m_textHeight(textHeight)
  {
    // Create shaders
    m_shaderProg = new ShaderProgram();
    m_shaderProg->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
    m_shaderProg->addShader(new FragmentShader("../resources/shader/frag_tex.glsl"));
    m_shaderProg->link();

    // Defualt colours
    m_itemColours[MenuItemState::NORMAL] = Colour(1.0f, 1.0f, 1.0f, 1.0f);
    m_itemColours[MenuItemState::HOVER] = Colour(0.8f, 0.9f, 1.0f, 1.0f);
    m_itemColours[MenuItemState::DISABLED] = Colour(0.5f, 0.5f, 0.5f, 1.0f);
  }

  IMenu::~IMenu()
  {
  }

  /**
   * @brief Gets the position of the menu origin.
   * @return Position of origin
   */
  Vector3 IMenu::position() const
  {
    return m_root->modelMatrix().positionVector();
  }

  /**
   * @brief Sets the position of the menu.
   * @param position New origin position
   */
  void IMenu::setPosition(const Vector3 &position)
  {
    m_root->setModelMatrix(Matrix4::Translation(position));
  }

  /**
   * @brief Tests if the menu is currently visible.
   * @return True if visible
   */
  bool IMenu::visible() const
  {
    return m_root->active();
  }

  /**
   * @brief Displays the menu.
   */
  void IMenu::show()
  {
    m_root->setActive(true, std::numeric_limits<size_t>::max());

    // Enable mouse event handling
    enable();
  }

  /**
   * @brief Hides the menu.
   */
  void IMenu::hide()
  {
    // Disable mouse event handling
    disable();

    m_root->setActive(false, std::numeric_limits<size_t>::max());
  }

  /**
   * @brief Adds a new basic item to the menu.
   * @param parent Parent item (nullptr to insert at root)
   * @param name Name of the item
   * @param text Text to be displayed on the item
   * @return Pointer to the new item
   */
  MenuItem *IMenu::addNewItem(MenuItem *parent, const std::string &name, const std::string &text)
  {
    MenuItem *item;

    if (parent == nullptr)
      item = new MenuItem(this, m_root, name);
    else
      item = new MenuItem(this, parent, name);

    if (!text.empty())
      item->setText(text);

    return item;
  }

  /**
   * @copydoc MouseHandler::handleButton
   */
  void IMenu::handleButton(const SDL_MouseButtonEvent &e)
  {
    if (e.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONUP && m_currentMouseOver != nullptr)
      handleMenuOptionSelection(m_currentMouseOver);
  }

  /**
   * @copydoc MouseHandler::handleMotion
   */
  void IMenu::handleMotion(const SDL_MouseMotionEvent &e)
  {
    std::pair<float, float> pos = MouseHandler::GetCentreNormalisedPos(e, m_game->windowX(), m_game->windowY());
    const Vector3 mousePos(pos.first, pos.second, 0.0f);
    checkMouseOver(mousePos, m_root);
  }

  /**
   * @brief Recursively checks for intersection between the mouse pointer and a menu option.
   * @param mousePos Position of the mouse in normalised screen space
   * @param node Node to test
   * @return True if intersection is detected
   */
  bool IMenu::checkMouseOver(const Vector3 &mousePos, SceneObject *node)
  {
    bool retVal = false;
    m_currentMouseOver = nullptr;

    for (SceneObject::SceneObjectListIter it = node->children().begin(); it != node->children().end(); ++it)
    {
      MenuItem *obj = static_cast<MenuItem *>(*it);
      Mesh *m = obj->mesh();
      if (obj->state() != MenuItemState::DISABLED)
      {
        auto bb = m->boundingBox();
        bb *= 1.15f;
        bb += obj->worldTransform().positionVector();

        bool mouseOver = bb.pointInside(mousePos);
        if (mouseOver)
          m_currentMouseOver = obj;

        if (mouseOver || (obj->state() == MenuItemState::HOVER && checkMouseOver(mousePos, obj)))
        {
          obj->setState(MenuItemState::HOVER);
          obj->setActive(true, 1);

          retVal = true;
        }
        else
        {
          obj->setState(MenuItemState::NORMAL);
          bool v = obj->active();
          obj->setActive(false, 1);
          obj->setActive(v);
        }
      }
    }

    return retVal;
  }
}
}
