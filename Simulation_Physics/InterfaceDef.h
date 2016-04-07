/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_PHYSICS_INTERFACEDEF_H_
#define _SIMULATION_PHYSICS_INTERFACEDEF_H_

namespace Simulation
{
namespace Physics
{
  /**
   * @class InterfaceDef
   * @brief Stores data about an interface between two Entity.
   * @author Dan Nixon
   */
  class InterfaceDef
  {
  public:
    /**
     * @brief Creates a new interface definition.
     * @param e1 First entity
     * @param e2 Second entity
     */
    InterfaceDef(Entity *e1, Entity *e2)
        : m_e1(e1)
        , m_e2(e2)
        , m_resolved(false)
    {
    }

    virtual ~InterfaceDef()
    {
    }

    /**
     * @brief Gets the first entity.
     * @return First entity
     */
    inline Entity *entityA()
    {
      return m_e1;
    }

    /**
     * @brief Gets the second entity.
     * @return Second entity
     */
    inline Entity *entityB()
    {
      return m_e2;
    }

    /**
     * @brief Retrieves the value of the resolution flag.
     * @return True if the interface has been resolved
     */
    inline bool resolved() const
    {
      return m_resolved;
    }

    /**
     * @brief Gets the interface normal.
     * @return Interface normal
     */
    inline Engine::Maths::Vector2 normal() const
    {
      return m_normal;
    }

    /**
     * @brief Tests to see if a given Entity participates in this interface.
     * @param e Entity to test
     * @return True if the given entity is part if this interface
     */
    inline bool contains(Entity *e) const
    {
      return (m_e1 == e) || (m_e2 == e);
    }

    /**
     * @brief Tests for equality between two interface definitions.
     * @param other Interface definition to compare to
     * @return True if definitions are equal
     *
     * Interface definitions are equal if they represent an interface between
     * the same two entities.
     */
    inline bool operator==(const InterfaceDef &other) const
    {
      return ((m_e1 == other.m_e1) && (m_e2 == other.m_e2)) || ((m_e1 == other.m_e2) && (m_e2 == other.m_e1));
    }

    /**
     * @brief Outputs an interface definition to a stream.
     * @param o Stream to output to
     * @param interf Interface definition to output
     * @return Reference to stream
     */
    inline friend std::ostream &operator<<(std::ostream &o, const InterfaceDef &interf)
    {
      o << "[" << *(interf.m_e1) << " - " << *(interf.m_e2) << "] (N=" << interf.m_normal << ")";
      return o;
    }

  private:
    friend class PhysicsSimulation;
    friend class InterfaceDetection;
    friend class InterfaceResolution;

    Entity *m_e1; //!< First entity
    Entity *m_e2; //!< Second entity

    bool m_resolved; //!< Flag indicating if the interface is resolved

    Engine::Maths::Vector2 m_normal; //!< Interface normal
  };
}
}

#endif
