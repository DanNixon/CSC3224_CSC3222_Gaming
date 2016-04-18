/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "PhysicalSystem.h"

namespace Engine
{
namespace Physics
{
  /**
   * @brief Create a new simulated physical system.
   * @param targetTimeStep Target time in milliseconds between physics updates
   * @param maxPossibleTimeStep The longest time in milliseconds between physics updates
   */
  PhysicalSystem::PhysicalSystem(float targetTimeStep, float maxPossibleTimeStep, float worldScale)
      : m_runSimulation(true)
      , m_targetTimeStep(targetTimeStep / 1000.0f)
      , m_maxSubSteps(static_cast<int>(maxPossibleTimeStep / targetTimeStep) + 1)
      , m_worldScale(worldScale)
      , m_broadphase(new btDbvtBroadphase())
      , m_collisionConfig(new btDefaultCollisionConfiguration())
      , m_solver(new btSequentialImpulseConstraintSolver())
  {
    m_collisionDispatcher = new btCollisionDispatcher(m_collisionConfig);
    m_world = new btDiscreteDynamicsWorld(m_collisionDispatcher, m_broadphase, m_solver, m_collisionConfig);

    // Real world gravity
    m_world->setGravity(btVector3(0.0f, -9.81f * m_worldScale, 0.0f));
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
   * @brief Sets the execution state of the physics simulation.
   * @param run If the simulation should be running
   */
  void PhysicalSystem::setSimulationState(bool run)
  {
    m_runSimulation = run;
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
    if (m_runSimulation)
      m_world->stepSimulation(msec * 0.001f, m_maxSubSteps, m_targetTimeStep);
  }
}
}
