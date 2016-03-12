/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_AUDIO_LISTENER_H_
#define _ENGINE_AUDIO_LISTENER_H_

#include <SceneObject.h>

namespace Engine
{
  namespace Audio
  {
    class Listener : public Engine::Common::SceneObject
    {
    public:
      Listener(const std::string &name);
      ~Listener();

      void use();
    };
  }
}

#endif