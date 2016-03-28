/**
 * @file
 * @author Dan Nixon
 */

#include "DemoGame.h"

#include <iostream>

#include <btBulletDynamicsCommon.h>

#include <MemoryManager.h>

#include "PhysicalSystem.h"
#include "PlanarRigidBody.h"
#include "SphericalRigidBody.h"

int main(int argc, char *args[])
{
  // TODO: physics testing
  Engine::Physics::PhysicalSystem *system = new Engine::Physics::PhysicalSystem();

  btDefaultMotionState *groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
  Engine::Physics::PlanarRigidBody *ground = new Engine::Physics::PlanarRigidBody(groundMotionState, 0, btVector3(0, 0, 0), btVector3(0, 1, 0));

  btDefaultMotionState *fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
  Engine::Physics::SphericalRigidBody *fall = new Engine::Physics::SphericalRigidBody(fallMotionState, 1, btVector3(0, 0, 0), 1);

  system->addBody(ground);
  system->addBody(fall);

  for (int i = 0; i < 300; i++)
  {
    system->update(1 / 60.f);

    btTransform trans;
    fall->motionState()->getWorldTransform(trans);

    std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
  }

  Engine::Common::MemoryManager::Instance().releaseAll();

  return 0;

  //GameDev::Demo::DemoGame g;
  //return g.run();
}
