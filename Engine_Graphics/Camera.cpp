/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "Camera.h"

#include <Engine_Graphics/Shader.h>
#include <Engine_Graphics/SphericalMesh.h>

using namespace Engine::Common;
using namespace Engine::Maths;

using namespace Engine::Graphics;

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Creates a new camera.
   * @param name Name of the camera
   * @param projection Projection matrix (default identity)
   * @param up Up vector (default Y axis)
   */
  Camera::Camera(const std::string &name, const Matrix4 &projection, const Vector3 &up)
      : RenderableObject(name) //, new SphericalMesh(10.0f), ShaderProgramLookup::Instance().get("ui_shader"))
      , m_up(up)
      , m_projection(projection)
  {
  }

  Camera::~Camera()
  {
  }

  /**
   * @copydoc SceneObject::update()
   */
  void Camera::update(float msec, Subsystem sys)
  {
    RenderableObject::update(msec, sys);

    if (sys == Subsystem::GRAPHICS && m_active)
    {
      m_scene->setProjectionMatrix(m_projection);
      m_scene->setViewMatrix(viewMatrix());
    }
  }

  /**
   * @brief Gets the view matrix for this camera.
   */
  Engine::Maths::Matrix4 Camera::viewMatrix() const
  {
    Vector3 position = m_worldTransform.positionVector();
    Vector3 facing;

    if (m_lookAt == nullptr)
      facing = position + m_worldTransform.facingVector();
    else
      facing = m_lookAt->worldTransform().positionVector();

    Matrix4 viewMat = Matrix4::BuildViewMatrix(position, facing, m_up);

    return viewMat;
  }
}
}
