/**
 * @file
 * @author Dan Nixon
 */

#include "PhysicalSystem.h"

namespace Engine
{
namespace Physics
{
  PhysicalSystem::PhysicalSystem()
      : m_broadphase(new btDbvtBroadphase())
      , m_collisionConfig(new btDefaultCollisionConfiguration())
      , m_solver(new btSequentialImpulseConstraintSolver())
  {
    m_collisionDispatcher = new btCollisionDispatcher(m_collisionConfig);
    m_world = new btDiscreteDynamicsWorld(m_collisionDispatcher, m_broadphase, m_solver, m_collisionConfig);
  }

  PhysicalSystem::~PhysicalSystem()
  {
    delete m_broadphase;
    delete m_collisionConfig;
    delete m_collisionDispatcher;
    delete m_solver;
    delete m_world;
  }

  void PhysicalSystem::addBody(RigidBody * body)
  {
    body->m_system = this;
    m_world->addRigidBody(body->m_body);
  }

  void PhysicalSystem::removeBody(RigidBody * body)
  {
    body->m_system = nullptr;
    m_world->removeRigidBody(body->m_body);
  }

  void PhysicalSystem::update(float msec)
  {
    m_world->stepSimulation(msec, 10);
  }
}
}
