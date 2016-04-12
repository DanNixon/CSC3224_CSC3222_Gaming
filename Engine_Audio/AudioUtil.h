/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_AUDIO_UTIL_H_
#define _ENGINE_AUDIO_UTIL_H_

#include <string>

#include <al.h>
#include <alc.h>

#include <Engine_Logging/Logger.h>

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

namespace Engine
{
namespace Audio
{
  /**
   * @class AudioUtil
   * @brief Contains utility functions for audio managment/processing.
   * @author Dan Nixon
   */
  class AudioUtil
  {
  public:
    /**
     * @brief Tests for an OpenAL error.
     * @param msg Error identification message
     * @return Ture if no error is found
     *
     * If error is found details are printed to stderr.
     */
    static bool CheckALError(const std::string &msg)
    {
      ALCenum error = alGetError();
      bool hasError = (error != AL_NO_ERROR);

      if (hasError)
        g_log.error("AL error " + std::to_string(error) + ": " + msg);

      return !hasError;
    }
  };
}
}

#endif
