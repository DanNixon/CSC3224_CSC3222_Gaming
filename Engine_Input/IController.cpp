/**
 * @file
 * @author Dan Nixon
 */

#include "IController.h"

namespace Engine
{
  namespace Input
  {
    IController::IController()
    {
    }

    IController::~IController()
    {
    }

    uint64_t IController::state() const
    {
      return m_state;
    }

    bool IController::state(uint64_t s) const
    {
      // TODO
      return false;
    }

    bool IController::hasAnalog(uint64_t a) const
    {
      return m_analogs.find(a) != m_analogs.end();
    }

    float IController::analog(uint64_t a) const
    {
      auto it = m_analogs.find(a);
      return (*it).second;;
    }

    void IController::setState(uint64_t s, bool active)
    {
      // TODO
    }
  }
}
