/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <bitset>
#include <list>
#include <map>

namespace Engine
{
namespace Common
{
  class Game;
}

namespace Input
{
  class IController;

  /**
   * @class IControlScheme
   * @brief Represents a collection of control devices and their mapping to
   *        analog and binary states.
   * @author Dan Nixon
   */
  class IControlScheme
  {
  public:
    /**
     * @var MAX_STATES
     * @brief Maximum number of binary states.
     */
    static const size_t MAX_STATES = 256;

    IControlScheme();
    virtual ~IControlScheme();

    void addController(IController *controller);
    void poll();

    bool state(size_t s) const;

    bool hasAnalog(size_t a) const;
    float analog(size_t a) const;

    virtual void setState(size_t state, bool active);
    virtual void flipState(size_t state);
    virtual void setAnalog(size_t state, float value);

  private:
    friend class IController;

    std::list<IController *> m_controllers; //!< All controls in this scheme

    std::bitset<MAX_STATES> m_state;   //!< Binary states
    std::map<size_t, float> m_analogs; //!< Analog states
  };
}
}
