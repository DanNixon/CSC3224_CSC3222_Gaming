/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _GAMEDEV_DEMO_TELEMETRYVALUEINDICATOR_H_
#define _GAMEDEV_DEMO_TELEMETRYVALUEINDICATOR_H_

#include <Engine_Common/SceneObject.h>

#include <Engine_Graphics/RenderableObject.h>
#include <Engine_Graphics/TextPane.h>

namespace GameDev
{
namespace Demo
{
  /**
   * @enum AlarmType
   * @brief Defines the alarm state for a telemetry value.
   * @author Dan Nixon
   */
  enum AlarmType : size_t
  {
    NORMAL,
    LOW,
    CRITICAL
  };

  /**
   * @class TelemetryValueIndicator
   * @brief Indicator for a telemetry value with alarm states.
   * @author Dan Nixon
   */
  class TelemetryValueIndicator : public Engine::Common::SceneObject
  {
  public:
    TelemetryValueIndicator(const std::string &name, Engine::Common::SceneObject *parent, const std::string &valueName);
    virtual ~TelemetryValueIndicator();

    void setValue(float value, size_t precision = 2);

    /**
     * @brief Sets the values at which alarms are triggered.
     * @param low Low alarm level
     * @param critical Critical alarm level
     */
    inline void setAlarmLevels(float low, float critical)
    {
      m_low = low;
      m_critical = critical;
    }

  private:
    void setAlarmState(AlarmType alarm);

  private:
    Engine::Graphics::Colour m_colours[3]; //!< Colour for each alarm state

    float m_low;      //!< Low alarm level
    float m_critical; //!< Critical alarm level

    AlarmType m_state; //!< Current state

    Engine::Graphics::RenderableObject *m_background; //!< Background rectangle
    Engine::Graphics::TextPane *m_nameText;           //!< Name text pane
    Engine::Graphics::TextPane *m_valueText;          //!< Value text pane
    Engine::Graphics::TextPane *m_alarmText;          //!< Alarm message text pane
  };
}
}

#endif
