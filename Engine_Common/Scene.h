/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include "Matrix4.h"

class SceneObject;

/**
 * @class Scene
 * @brief Represents a 3D scene.
 */
class Scene
{
public:
  Scene(SceneObject *root, Matrix4 view = Matrix4(),
        Matrix4 projection = Matrix4());
  virtual ~Scene();

  void setViewMatrix(Matrix4 view);
  Matrix4 viewMatrix();

  void setProjectionMatrix(Matrix4 projection);
  Matrix4 projectionMatrix();

  void update();
  void render();

private:
  SceneObject *m_root;        //!< Root node in the scene tree
  Matrix4 m_viewMatrix;       //!< View matrix
  Matrix4 m_projectionMatrix; //!< Projection matrix
};
