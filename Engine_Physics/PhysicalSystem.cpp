/**
 * @file
 * @author Dan Nixon
 */

#include "PhysicalSystem.h"

namespace Engine
{
namespace Physics
{
  /**
   * @brief Create a new simulated physical system.
   */
  PhysicalSystem::PhysicalSystem()
      : m_broadphase(new btDbvtBroadphase())
      , m_collisionConfig(new btDefaultCollisionConfiguration())
      , m_solver(new btSequentialImpulseConstraintSolver())
  {
    m_collisionDispatcher = new btCollisionDispatcher(m_collisionConfig);
    m_world = new btDiscreteDynamicsWorld(m_collisionDispatcher, m_broadphase, m_solver, m_collisionConfig);

    // Real world gravity
    m_world->setGravity(btVector3(0.0f, -9.81f, 0.0f));
  }

  PhysicalSystem::~PhysicalSystem()
  {
    delete m_broadphase;
    delete m_collisionConfig;
    delete m_collisionDispatcher;
    delete m_solver;
    delete m_world;
  }

  /**
   * @brief Adds a rigid body to the simulation.
   * @param body Rigid body
   */
  void PhysicalSystem::addBody(RigidBody *body)
  {
    body->m_system = this;
    m_world->addRigidBody(body->m_body);
  }

  /**
   * @brief Removes a rigid body from the simulation.
   * @param body Rigid body
   */
  void PhysicalSystem::removeBody(RigidBody *body)
  {
    body->m_system = nullptr;
    m_world->removeRigidBody(body->m_body);
  }

  /**
   * @brief Steps the simulation.
   * @param msec Time in milliseconds since last update
   */
  void PhysicalSystem::update(float msec)
  {
    // TODO: make target frame rate a parameter to constructor
    m_world->stepSimulation(msec / 1000.0f, 7, 1.0f / 120.0f);
  }
}
}
