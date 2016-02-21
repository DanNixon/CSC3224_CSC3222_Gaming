/**
* @file
* @author Dan Nixon
*/

#pragma once

#include <IEventHandler.h>

#include <SDL.h>

namespace Engine
{
namespace Input
{
  class JoystickHandler : public Engine::Common::IEventHandler
  {
  public:
    static int NumJoysticks();

    JoystickHandler();
    virtual ~JoystickHandler();

    bool open(int deviceIndex);
    void close();

    bool button(int button) const;
    Sint32 axis(int axis) const;

  protected:
    virtual void handleEvent(const SDL_Event &e);

    virtual void handleButton(const SDL_JoyButtonEvent &e) = 0;
    virtual void handleMotion(const SDL_JoyAxisEvent &e) = 0;

  private:
    SDL_Joystick *m_joystick;
  };
}
}