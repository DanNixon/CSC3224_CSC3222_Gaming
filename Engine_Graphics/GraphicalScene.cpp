/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "GraphicalScene.h"

#include "RenderableObject.h"

using namespace Engine::Common;
using namespace Engine::Maths;

namespace Engine
{
namespace Graphics
{
  /**
   * @copydoc Scene::Scene
   */
  GraphicalScene::GraphicalScene(SceneObject *root, Matrix4 view, Matrix4 projection)
      : Scene(root, view, projection)
  {
  }

  GraphicalScene::~GraphicalScene()
  {
  }

  /**
   * @copydoc Scene::update
   */
  void GraphicalScene::update(float msec, Subsystem sys)
  {
    Scene::update(msec, sys);

    if (sys == Subsystem::GRAPHICS)
    {
      for (auto it = m_transparent.begin(); it != m_transparent.end(); ++it)
        (*it)->render();

      m_transparent.clear();
    }
  }
}
}
