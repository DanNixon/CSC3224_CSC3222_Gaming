/**
 * @file
 * @author Dan Nixon
 */

#include "Scene.h"

#include "SceneObject.h"

using namespace Engine::Maths;

namespace Engine
{
namespace Common
{
  /**
   * @brief Creates a new scene.
   * @param root Root node in the scene
   * @param view View matrix
   * @param projection Projection matrix
   */
  Scene::Scene(SceneObject *root, Matrix4 view, Matrix4 projection)
      : m_root(root)
      , m_viewMatrix(view)
      , m_projectionMatrix(projection)
  {
    root->addToScene(this);
  }

  Scene::~Scene()
  {
  }

  /**
   * @brief Sets the view matrix.
   * @param view View matrix
   */
  void Scene::setViewMatrix(Matrix4 view)
  {
    m_viewMatrix = view;
  }

  /**
   * @brief Gets the view matrix.
   * @return View matrix
   */
  Matrix4 Scene::viewMatrix()
  {
    return m_viewMatrix;
  }

  /**
   * @brief Sets the projection matrix.
   * @param projection Projection matrix
   */
  void Scene::setProjectionMatrix(Matrix4 projection)
  {
    m_projectionMatrix = projection;
  }

  /**
   * @brief Gets the projection matrix.
   * @return Projection matrix
   */
  Matrix4 Scene::projectionMatrix()
  {
    return m_projectionMatrix;
  }

  /**
   * @brief Updates elements in the scene.
   * @param msec Time since last update (in milliseconds)
   * @param sys Subsystem being updated
   */
  void Scene::update(float msec, Subsystem sys)
  {
    m_root->update(msec, sys);
  }
}
}
