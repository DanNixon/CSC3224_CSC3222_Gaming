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
  enum AlarmType : size_t
  {
    NORMAL,
    LOW,
    CRITICAL
  };

  /**
   * @class TelemetryValueIndicator
   * @brief TODO
   * @author Dan Nixon
   */
  class TelemetryValueIndicator : public Engine::Common::SceneObject
  {
  public:
    TelemetryValueIndicator(const std::string &name, Engine::Common::SceneObject *parent, const std::string &valueName);
    virtual ~TelemetryValueIndicator();

    void setValue(float value, size_t precision = 2);

    inline void setAlarmLevels(float low, float critical)
    {
      m_low = low;
      m_critical = critical;
    }

  private:
    void setAlarmState(AlarmType alarm);

  private:
    Engine::Graphics::Colour m_colours[3];

    float m_low;
    float m_critical;

    AlarmType m_state;

    Engine::Graphics::RenderableObject *m_background;
    Engine::Graphics::TextPane *m_nameText;
    Engine::Graphics::TextPane *m_valueText;
    Engine::Graphics::TextPane *m_alarmText;
  };
}
}

#endif