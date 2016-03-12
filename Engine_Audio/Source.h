/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_AUDIO_SOURCE_H_
#define _ENGINE_AUDIO_SOURCE_H_

#include <SceneObject.h>

#include <al.h>

namespace Engine
{
  namespace Audio
  {
    class Source : public Engine::Common::SceneObject
    {
    public:
      Source(const std::string &name);
      ~Source();

      bool valid() const;

      bool setLooping(bool loop);

      bool play();
      bool stop();

      bool isPlaying() const;

      ALuint id() const
      {
        return m_sourceID;
      }

      ALuint buffer() const
      {
        return m_buffer;
      }

      virtual void update(float msec);

    private:
      ALuint m_sourceID;
      ALuint m_buffer;
    };
  }
}

#endif