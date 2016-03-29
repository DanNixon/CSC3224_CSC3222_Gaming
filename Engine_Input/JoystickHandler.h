/**
* @file
* @author Dan Nixon
*/

#ifndef _ENGINE_INPUT_JOYSTICKHANDLER_H_
#define _ENGINE_INPUT_JOYSTICKHANDLER_H_

#include <Engine_Common/IEventHandler.h>

namespace Engine
{
namespace Input
{
  /**
   * @class JoystickHandler
   * @brief Abstract class for handling joystick input.
   * @author Dan Nixon
   */
  class JoystickHandler : public Engine::Common::IEventHandler
  {
  public:
    static int NumJoysticks();

    JoystickHandler();
    virtual ~JoystickHandler();

    bool open(int deviceIndex);
    void close();
    bool isOpen() const;

    int numButtons() const;
    int numAxes() const;

    bool button(int button) const;
    Sint32 axis(int axis) const;

  protected:
    virtual void handleEvent(const SDL_Event &e);

    /**
     * @brief Handles a button being pressed or released.
     * @param e Event
     */
    virtual void handleButton(const SDL_JoyButtonEvent &e) = 0;

    /**
     * @brief Handles an axis of the joystick being moved.
     * @param e Event
     */
    virtual void handleMotion(const SDL_JoyAxisEvent &e) = 0;

  private:
    SDL_Joystick *m_joystick; //!< Currently open joystick
  };
}
}

#endif