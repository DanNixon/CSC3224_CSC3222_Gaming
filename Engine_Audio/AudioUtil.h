/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_AUDIO_UTIL_H_
#define _ENGINE_AUDIO_UTIL_H_

#include <string>
#include <iostream>

#include <al.h>
#include <alc.h>

namespace Engine
{
  namespace Audio
  {
    class AudioUtil
    {
    public:
      static bool CheckALError(const std::string &msg)
      {
        ALCenum error = alGetError();
        bool hasError = (error != AL_NO_ERROR);

        if (hasError)
          std::cerr << "AL error " << error << " (" << msg << ")" << std::endl;

        return !hasError;
      }
    };
  }
}

#endif