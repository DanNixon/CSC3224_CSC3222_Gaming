/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "TelemetryValueIndicator.h"

#include <sstream>

#include <Engine_Graphics/RectangleMesh.h>

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;

namespace GameDev
{
namespace FlightSim
{
  /**
   * @brief Creates a new telemetry value indicator.
   * @param name Name of the value
   * @param parent Parent SceneObject
   * @param valueName Displayed name of the value
   */
  TelemetryValueIndicator::TelemetryValueIndicator(const std::string &name, SceneObject *parent,
                                                   const std::string &valueName)
      : SceneObject(name, parent)
      , m_low(0.0f)
      , m_critical(0.0f)
  {
    // Default colours
    m_colours[AlarmType::NORMAL] = Colour(0.1f, 0.5f, 0.1f);
    m_colours[AlarmType::LOW] = Colour(0.5f, 0.5f, 0.0f);
    m_colours[AlarmType::CRITICAL] = Colour(0.5f, 0.1f, 0.1f);

    ShaderProgram *shaderProgram = ShaderProgramLookup::Instance().get("menu_shader");
    TTF_Font *font = TTFFontLookup::Instance().get("main_font");

    // Background rectangle
    m_background = new RenderableObject("area", new RectangleMesh(Vector2(2.0f, 1.8f)),
                                        ShaderProgramLookup::Instance().get("ui_shader"));
    addChild(m_background);

    // Name text
    m_nameText = new TextPane("name", 0.5f, shaderProgram, font, TextMode::SHADED);
    m_nameText->setTextColour(Colour(0.0f, 0.0f, 0.0f));
    m_nameText->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.6f, -0.1f)));
    m_nameText->setText(valueName);
    m_background->addChild(m_nameText);

    // Value text
    m_valueText = new TextPane("value", 1.0f, shaderProgram, font, TextMode::SHADED);
    m_valueText->setTextColour(Colour(0.0f, 0.0f, 0.0f));
    m_valueText->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.0f, -0.05f)));
    m_background->addChild(m_valueText);

    // Warning text
    m_alarmText = new TextPane("alarm", 0.6f, shaderProgram, font, TextMode::SHADED);
    m_alarmText->setTextColour(Colour(0.0f, 0.0f, 0.0f));
    m_alarmText->setModelMatrix(Matrix4::Translation(Vector3(0.0f, -0.6f, -0.1f)));
    m_background->addChild(m_alarmText);

    // Default state
    setValue(0.1f, 2);
    setAlarmState(AlarmType::NORMAL);
  }

  TelemetryValueIndicator::~TelemetryValueIndicator()
  {
  }

  /**
   * @brief Sets the value.
   * @param value Value
   * @param precision Display precision
   */
  void TelemetryValueIndicator::setValue(float value, size_t precision)
  {
    // Update value display
    std::stringstream str;
    str.precision(precision);
    str << value;
    m_valueText->setText(str.str());

    // Update state
    AlarmType currentState;
    if (value < m_critical)
      currentState = AlarmType::CRITICAL;
    else if (value < m_low)
      currentState = AlarmType::LOW;
    else
      currentState = AlarmType::NORMAL;

    // Update background colour if needed
    if (m_state != currentState)
    {
      m_state = currentState;
      setAlarmState(currentState);
    }
  }

  /**
   * @brief Updates the alarm state.
   * @param alarm Alarm state
   */
  void TelemetryValueIndicator::setAlarmState(AlarmType alarm)
  {
    // Update background colour
    const Colour &colour = m_colours[alarm];
    m_background->mesh()->setStaticColour(colour);
    m_nameText->setBackgroundColour(colour);
    m_valueText->setBackgroundColour(colour);
    m_alarmText->setBackgroundColour(colour);

    // Update alarm text
    switch (alarm)
    {
    case AlarmType::LOW:
      m_alarmText->setActive(true && m_active);
      m_alarmText->setText("LOW");
      break;
    case AlarmType::CRITICAL:
      m_alarmText->setActive(true && m_active);
      m_alarmText->setText("CRITICAL");
      break;
    default:
      m_alarmText->setActive(false);
    }
  }
}
}
