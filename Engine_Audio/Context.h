/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_AUDIO_CONTEXT_H_
#define _ENGINE_AUDIO_CONTEXT_H_

#include <vector>

#include <alc.h>

namespace Engine
{
  namespace Audio
  {
    class Context
    {
    public:
      Context();
      virtual ~Context();

      bool open();
      void close();
      bool isOpen() const;

      inline ALCdevice *getDevice()
      {
        return m_device;
      }

      inline ALCcontext *getContext()
      {
        return m_context;
      }

    private:
      ALCdevice * m_device;
      ALCcontext * m_context;
    };
  }
}

#endif