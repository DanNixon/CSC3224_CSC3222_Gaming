/**
 * @file
 * @author Dan Nixon
 */

#include "IControlScheme.h"

#include <Game.h>
#include <IEventHandler.h>

using namespace Engine::Common;

namespace Engine
{
  namespace Input
  {
    IControlScheme::IControlScheme()
    {
    }

    IControlScheme::~IControlScheme()
    {
    }

    void IControlScheme::addController(IController * controller)
    {
      m_controllers.push_back(controller);
    }

    bool IControlScheme::state(size_t s) const
    {
      return m_state[s];
    }

    bool IControlScheme::hasAnalog(size_t a) const
    {
      return m_analogs.find(a) != m_analogs.end();
    }

    float IControlScheme::analog(size_t a) const
    {
      auto it = m_analogs.find(a);
      if (it == m_analogs.end())
        return 0.0f;
      return (*it).second;
    }

    void IControlScheme::setState(size_t state, bool active)
    {
      m_state.set(state, active);
    }

    void IControlScheme::setAnalog(size_t state, float value)
    {
      m_analogs[state] = value;
    }
  }
}