/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _GAMEDEV_DEMO_STICKINDICATOR_H_
#define _GAMEDEV_DEMO_STICKINDICATOR_H_

#include <Engine_Common/SceneObject.h>

#include <Engine_Graphics/RenderableObject.h>

namespace GameDev
{
namespace FlightSim
{
  /**
   * @class StickIndicator
   * @brief Display for stick position.
   * @author Dan Nixon
   */
  class StickIndicator : public Engine::Common::SceneObject
  {
  public:
    StickIndicator(const std::string &name, Engine::Common::SceneObject *parent);
    virtual ~StickIndicator();

    void setStickPosition(float horizontal, float vertical);

  private:
    Engine::Graphics::RenderableObject *m_background; //!< Background rectangle
    Engine::Graphics::RenderableObject *m_indicator;  //!< Indicator circle
  };
}
}

#endif
