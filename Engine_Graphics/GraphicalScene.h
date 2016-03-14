/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_GRAPHICALSCENE_H_
#define _ENGINE_GRAPHICS_GRAPHICALSCENE_H_

#include <Scene.h>

#include <vector>

#include <SceneObject.h>
#include <Subsystem.h>

namespace Engine
{
namespace Graphics
{
  class RenderableObject;

  /**
   * @class GraphicalScene
   * @brief An extension to Scene that renders transparent objects last.
   * @author Dan Nixon
   */
  class GraphicalScene : public Engine::Common::Scene
  {
  public:
    GraphicalScene(Engine::Common::SceneObject *root, Engine::Maths::Matrix4 view = Engine::Maths::Matrix4(),
                   Engine::Maths::Matrix4 projection = Engine::Maths::Matrix4());
    virtual ~GraphicalScene();

    virtual void update(float msec, Engine::Common::Subsystem sys);

  protected:
    friend class RenderableObject;

    std::vector<RenderableObject *> m_transparent; //!< Transparent objects to be rendered last
  };
}
}

#endif
