/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include "Matrix4.h"

namespace Engine
{
namespace Common
{

class SceneObject;

/**
 * @class Scene
 * @brief Represents a 3D scene.
 */
class Scene
{
public:
  Scene(SceneObject *root, Engine::Maths::Matrix4 view = Engine::Maths::Matrix4(),
    Engine::Maths::Matrix4 projection = Engine::Maths::Matrix4());
  virtual ~Scene();

  void setViewMatrix(Engine::Maths::Matrix4 view);
  Engine::Maths::Matrix4 viewMatrix();

  void setProjectionMatrix(Engine::Maths::Matrix4 projection);
  Engine::Maths::Matrix4 projectionMatrix();

  void update();
  void render();

private:
  SceneObject *m_root;        //!< Root node in the scene tree
  Engine::Maths::Matrix4 m_viewMatrix;       //!< View matrix
  Engine::Maths::Matrix4 m_projectionMatrix; //!< Projection matrix
};
}
}
