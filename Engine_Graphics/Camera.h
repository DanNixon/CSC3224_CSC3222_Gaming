/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_CAMERA_H_
#define _ENGINE_GRAPHICS_CAMERA_H_

#include <Engine_Common/SceneObject.h>
#include <Engine_Graphics/RenderableObject.h>

namespace Engine
{
namespace Graphics
{
  /**
   * @class Camera
   * @brief Represents a camera in a scene.
   * @author Dan Nixon
   */
  class Camera : public Engine::Graphics::RenderableObject // Engine::Common::SceneObject
  {
  public:
    Camera(const std::string &name, const Engine::Maths::Matrix4 &projection = Engine::Maths::Matrix4(),
           const Engine::Maths::Vector3 &up = Engine::Maths::Vector3(0.0f, 1.0f, 0.0f));
    virtual ~Camera();

    virtual void update(float msec, Engine::Common::Subsystem sys);

    /**
     * @brief Sets the object that the camera is looking at.
     * @param object Object to look at
     */
    inline void lookAt(Engine::Common::SceneObject *object)
    {
      m_lookAt = object;
    }

    /**
     * @brief Point the camera in a given sirection.
     * @param direction DIrection to look in
     *
     * Only takes affect when lookAt() is either not claled or was last called
     * with nullptr as the parameter.
     */
    inline void look(Engine::Maths::Vector3 direction)
    {
      m_lookDirection = direction;
    }

    /**
     * @brief Sets the projection matrix.
     * @param projection Projection matrix
     */
    inline void setProjectionMatrix(const Engine::Maths::Matrix4 &projection)
    {
      m_projection = projection;
    }

    /**
     * @brief Gets the projection matrix.
     * @return Projection matrix
     */
    inline Engine::Maths::Matrix4 projectionMatrix() const
    {
      return m_projection;
    }

    Engine::Maths::Matrix4 viewMatrix() const;

  protected:
    Engine::Maths::Vector3 m_up;            //!< Up vector
    Engine::Maths::Matrix4 m_projection;    //!< Projection matrix
    Engine::Maths::Vector3 m_lookDirection; //!< Direction to look in
    Engine::Common::SceneObject *m_lookAt;  //!< Object to look at
  };
}
}

#endif
