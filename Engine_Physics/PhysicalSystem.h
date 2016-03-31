/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_PHYSICS_PHYSICALSYSTEM_H_
#define _ENGINE_PHYSICS_PHYSICALSYSTEM_H_

#include <btBulletDynamicsCommon.h>

#include <Engine_Common/IMemoryManaged.h>

#include "RigidBody.h"

namespace Engine
{
namespace Physics
{
  /**
   * @class PhysicalSystem
   * @brief Used to manage a simulated physical system.
   * @author Dan Nixon
   */
  class PhysicalSystem : public Engine::Common::IMemoryManaged
  {
  public:
    PhysicalSystem(float targetTimeStep, float maxPossibleTimeStep);
    virtual ~PhysicalSystem();

    /**
     * @copydoc IMemoryManaged::releaseOrder
     */
    virtual int releaseOrder() const
    {
      return 50;
    }

    /**
     * @brief Gets the target time between simulation updates in milliseconds.
     * @return Target time step
     */
    float targetTimeStep() const
    {
      return m_targetTimeStep;
    }

    /**
     * @brief Gets the maximum number of sub steps for a simulation update.
     * @return Maximum number of sub steps
     */
    int maxSubSteps() const
    {
      return m_maxSubSteps;
    }

    void setSimulationState(bool run);

    /**
     * @brief Checks if the physics simulation is currently running.
     * @return True if simulation is running
     */
    inline bool simulationRunning() const
    {
      return m_runSimulation;
    }

    void addBody(RigidBody *body);
    void removeBody(RigidBody *body);

    void update(float msec);

  private:
    bool m_runSimulation;   //!< Flag indicating if the simulation should be running
    float m_targetTimeStep; //!< Target time between simulation updates (ms)
    int m_maxSubSteps;      //!< Maximum sub steps for simulation update
    btBroadphaseInterface *m_broadphase;
    btDefaultCollisionConfiguration *m_collisionConfig;
    btCollisionDispatcher *m_collisionDispatcher;
    btSequentialImpulseConstraintSolver *m_solver;
    btDiscreteDynamicsWorld *m_world;
  };
}
}

#endif