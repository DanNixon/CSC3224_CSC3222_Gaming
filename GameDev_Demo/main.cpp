/**
 * @file
 * @author Dan Nixon
 */

#include "DemoGame.h"

#include <iostream>

#include <btBulletDynamicsCommon.h>

#include <MemoryManager.h>
#include <Quaternion.h>
#include <PhysicalSystem.h>
#include <StaticPlaneRigidBody.h>
#include <SphericalRigidBody.h>

using namespace Engine::Common;
using namespace Engine::Maths;
using namespace Engine::Physics;

int main(int argc, char *args[])
{
  // Physics testing
  Engine::Physics::PhysicalSystem *system = new Engine::Physics::PhysicalSystem();

  Engine::Common::SceneObject *ground = new Engine::Common::SceneObject("ground");
  SceneObjectMotionState *groundMotionState = new Engine::Physics::SceneObjectMotionState(ground, Vector3(0.0f, 0.0f, 0.0f), Quaternion());
  Engine::Physics::RigidBody *groundBody = new Engine::Physics::StaticPlaneRigidBody(groundMotionState, 0, btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 1.0f, 0.0f));

  Engine::Common::SceneObject *ball = new Engine::Common::SceneObject("ball");
  SceneObjectMotionState *ballMotionState = new Engine::Physics::SceneObjectMotionState(ball, Vector3(0.0f, 50.0f, 0.0f), Quaternion(0.0f, 30.0f, 0.0f));
  //Engine::Physics::RigidBody *ballBody = new Engine::Physics::SphericalRigidBody(ballMotionState, 1.0f, btVector3(0.0f, 0.0f, 0.0f), 1.0f);
  btCollisionShape * ballShape = new btBoxShape(btVector3(5, 5, 5));
  Engine::Physics::RigidBody *ballBody = new Engine::Physics::RigidBody(ballMotionState, 1.0f, btVector3(0.0f, 0.0f, 0.0f), ballShape);

  system->addBody(groundBody);
  system->addBody(ballBody);

  for (int i = 0; i < 300; i++)
  {
    system->update(1 / 60.f);

    std::cout << i << ": pos=" << ball->modelMatrix().positionVector() <<
                " up=" << ball->modelMatrix().upVector() << std::endl;
  }

  Engine::Common::MemoryManager::Instance().releaseAll();

  return 0;

  // TODO
  //GameDev::Demo::DemoGame g;
  //return g.run();
}
