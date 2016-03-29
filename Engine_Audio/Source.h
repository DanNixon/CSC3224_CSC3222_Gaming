/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_AUDIO_SOURCE_H_
#define _ENGINE_AUDIO_SOURCE_H_

#include <Engine_Common/SceneObject.h>

#include <al.h>

#include "Listener.h"

namespace Engine
{
namespace Audio
{
  /**
   * @class Source
   * @brief Represents a sound source.
   * @author Dan Nixon
   */
  class Source : public Engine::Common::SceneObject
  {
  public:
    Source(const std::string &name, Listener *listener);
    virtual ~Source();

    virtual bool valid() const;

    bool setLooping(bool loop);

    bool play();
    bool stop();

    bool isPlaying() const;

    /**
     * @brief Gets the source ID.
     * @return Source ID
     */
    ALuint id() const
    {
      return m_sourceID;
    }

    /**
     * @brief Gets the buffer used for this source.
     * @return Buffer
     */
    ALuint buffer() const
    {
      return m_buffer;
    }

    virtual void update(float msec, Engine::Common::Subsystem sys);

  protected:
    ALuint m_sourceID;    //!< Source ID
    ALuint m_buffer;      //!< Buffer used for source
    Listener *m_listener; //!< Listener used to output sound to
  };
}
}

#endif
