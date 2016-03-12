/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_AUDIO_WAVSOURCE_H_
#define _ENGINE_AUDIO_WAVSOURCE_H_

#include "Source.h"

namespace Engine
{
  namespace Audio
  {
    class WAVSource : public Source
    {
    public:
      WAVSource(const std::string &name, Listener * listener);
      virtual ~WAVSource();

      bool load(const std::string &filename);
    };
  }
}

#endif