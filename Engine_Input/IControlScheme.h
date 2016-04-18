/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#pragma once

#include <bitset>
#include <list>
#include <map>

#include <Engine_Common/Game.h>
#include <Engine_ResourceManagment/IMemoryManaged.h>

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
  class IControlScheme : public Engine::ResourceManagment::IMemoryManaged
  {
  public:
    /**
     * @var MAX_STATES
     * @brief Maximum number of binary states.
     */
    static const size_t MAX_STATES = 256;

    IControlScheme(Engine::Common::Game *game);
    virtual ~IControlScheme();

    void addController(IController *controller);
    void poll();

    /**
     * @brief Gets a binary state.
     * @param s State ID
     * @return Value of state
     */
    inline bool state(size_t s) const
    {
      return m_state[s];
    }

    bool hasAnalog(size_t a) const;
    float analog(size_t a) const;

    void setAnalogDeadbands(float deadbandCentre = 0.0f, float deadbandLimit = 0.0f);
    void setAnalogLimits(float minValue, float maxValue);

    virtual void setState(size_t state, bool active);
    virtual void flipState(size_t state);
    virtual void setAnalog(size_t state, float value);

  protected:
    Engine::Common::Game *m_game; //!< Game instance control scheme is used in

  private:
    friend class IController;

    std::list<IController *> m_controllers; //!< All controls in this scheme

    std::bitset<MAX_STATES> m_state;   //!< Binary states
    std::map<size_t, float> m_analogs; //!< Analog states

    float m_analogDeadbands[3];
    float m_analogLimits[2];
  };
}
}
