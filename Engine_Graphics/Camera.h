/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_CAMERA_H_
#define _ENGINE_GRAPHICS_CAMERA_H_

#include <Engine_Common/SceneObject.h>

namespace Engine
{
namespace Graphics
{
  /**
   * @class Camera
   * @brief Represents a camera in a scene.
   * @author Dan Nixon
   */
  class Camera : public Engine::Common::SceneObject
  {
  public:
    Camera(const std::string &name, const Engine::Maths::Matrix4 &projection = Engine::Maths::Matrix4(),
           const Engine::Maths::Vector3 &up = Engine::Maths::Vector3(0.0f, 1.0f, 0.0f));
    ~Camera();

    virtual void update(float msec, Engine::Common::Subsystem sys);

    inline void lookAt(Engine::Common::SceneObject *object)
    {
      m_lookAt = object;
    }

    inline void look(Engine::Maths::Vector3 direction)
    {
      m_lookDirection = direction;
    }

    inline void setProjectionMatrix(const Engine::Maths::Matrix4 &projection)
    {
      m_projection = projection;
    }

    inline Engine::Maths::Matrix4 projectionMatrix() const
    {
      return m_projection;
    }

    Engine::Maths::Matrix4 viewMatrix() const;

  protected:
    Engine::Maths::Vector3 m_up;
    Engine::Maths::Matrix4 m_projection;
    Engine::Maths::Vector3 m_lookDirection;
    Engine::Common::SceneObject *m_lookAt;
  };
}
}

#endif
