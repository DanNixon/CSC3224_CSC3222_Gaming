/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <bitset>
#include <map>
#include <list>

namespace Engine
{
  namespace Common
  {
    class Game;
  }

  namespace Input
  {
    class IController;

    class IControlScheme
    {
    public:
      static const size_t MAX_STATES = 256;

      IControlScheme();
      virtual ~IControlScheme();

      void addController(IController * controller);
      void poll();

      bool state(size_t s) const;

      bool hasAnalog(size_t a) const;
      float analog(size_t a) const;

      virtual void setState(size_t state, bool active);
      virtual void setAnalog(size_t state, float value);

    private:
      friend class IController;

      std::list<IController *> m_controllers;

      std::bitset<MAX_STATES> m_state;
      std::map<size_t, float> m_analogs;
    };
  }
}