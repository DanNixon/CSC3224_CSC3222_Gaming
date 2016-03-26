/**
 * @file
 * @author Dan Nixon
 */

#include "SceneObjectMotionState.h"

#include <Matrix4.h>
#include <Quaternion.h>
#include <Vector3.h>

using namespace Engine::Common;
using namespace Engine::Maths;

namespace Engine
{
namespace Physics
{
  SceneObjectMotionState::SceneObjectMotionState(const btTransform &initialPosition, SceneObject *object)
      : m_initialPosition(initialPosition)
      , m_sceneObject(object)
  {
  }

  SceneObjectMotionState::~SceneObjectMotionState()
  {
  }

  void SceneObjectMotionState::setSceneObject(Engine::Common::SceneObject *object)
  {
    m_sceneObject = object;
  }

  void SceneObjectMotionState::getWorldTransform(btTransform &worldTrans) const
  {
    worldTrans = m_initialPosition;
  }

  void SceneObjectMotionState::setWorldTransform(const btTransform &worldTrans)
  {
    if (m_sceneObject == nullptr)
      return;

    btQuaternion rot = worldTrans.getRotation();
    btVector3 pos = worldTrans.getOrigin();

    Quaternion rotQuat(rot.w(), rot.x(), rot.y(), rot.z());
    Vector3 posVec(pos.x(), pos.y(), pos.z());

    Matrix4 modelMat = m_sceneObject->modelMatrix() * rotQuat.rotationMatrix() * Matrix4::Translation(posVec);
    m_sceneObject->setModelMatrix(modelMat);
  }
}
}