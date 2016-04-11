/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_AUDIO_LISTENER_H_
#define _ENGINE_AUDIO_LISTENER_H_

#include <Engine_Common/SceneObject.h>

namespace Engine
{
namespace Audio
{
  /**
   * @class Listener
   * @brief Represents an audio listener.
   * @author Dan Nixon
   */
  class Listener : public Engine::Common::SceneObject
  {
  public:
    Listener(const std::string &name);
    virtual ~Listener();

    void use();
  };
}
}

#endif
