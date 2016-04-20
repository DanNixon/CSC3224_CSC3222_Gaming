/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_GRAPHICALSCENE_H_
#define _ENGINE_GRAPHICS_GRAPHICALSCENE_H_

#include <Engine_Common/Scene.h>

#include <vector>

#include <Engine_Common/SceneObject.h>
#include <Engine_Common/Subsystem.h>

#include "Light.h"

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

    /**
     * @brief Gets a reference to the list of lights.
     * @return Lights
     */
    inline std::vector<Light *> &lights()
    {
      return m_lights;
    }

    virtual void update(float msec, Engine::Common::Subsystem sys);

  protected:
    friend class RenderableObject;

    std::vector<RenderableObject *> m_transparent; //!< Transparent objects to be rendered last
    std::vector<Light *> m_lights;                 //!< List of all lights in a scene
  };
}
}

#endif
