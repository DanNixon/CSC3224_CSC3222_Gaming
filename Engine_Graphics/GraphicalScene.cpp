/**
 * @file
 * @author Dan Nixon
 */

#include "GraphicalScene.h"

#include "RenderableObject.h"

using namespace Engine::Common;
using namespace Engine::Maths;

namespace Engine
{
namespace Graphics
{
  GraphicalScene::GraphicalScene(SceneObject *root, Matrix4 view, Matrix4 projection)
      : Scene(root, view, projection)
  {
  }

  GraphicalScene::~GraphicalScene()
  {
  }

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