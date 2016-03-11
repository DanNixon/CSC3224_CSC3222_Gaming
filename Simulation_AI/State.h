/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_AI_STATE_H_
#define _SIMULATION_AI_STATE_H_

namespace Simulation
{
namespace AI
{
  class State
  {
  public:
    State(State *parent);
    virtual ~State();

    virtual void operate() = 0;

    virtual State *transferCheck() const = 0;

  protected:
    State *m_parent;
    std::vector<State *> m_children;
  };
}
}

#endif
