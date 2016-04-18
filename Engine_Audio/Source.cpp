/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "Source.h"

#include <Engine_Common/Subsystem.h>
#include <Engine_Maths/Vector4.h>

#include "AudioUtil.h"

using namespace Engine::Common;
using namespace Engine::Maths;

namespace Engine
{
namespace Audio
{
  /**
   * @copydoc SceneObject::SceneObject
   * @param listener Listener to use for output
   */
  Source::Source(const std::string &name, Listener *listener)
      : SceneObject(name)
      , m_listener(listener)
  {
    alGenSources(1, &m_sourceID);
    alGenBuffers(1, &m_buffer);

    alSourcei(m_sourceID, AL_BUFFER, m_buffer);

    alSourcef(m_sourceID, AL_PITCH, 1);
    alSourcef(m_sourceID, AL_GAIN, 50);

    setLooping(false);
  }

  Source::~Source()
  {
    alSourcei(m_sourceID, AL_BUFFER, 0);

    alDeleteSources(1, &m_sourceID);
    alDeleteBuffers(1, &m_buffer);
  }

  /**
   * @brief Tests if the source is valid.
   * @return True if source is valid
   */
  bool Source::valid() const
  {
    return (m_sourceID > 0 && m_buffer > 0 && m_listener);
  }

  /**
   * @brief Sets if the source should play one of loop.
   * @param loop If source should loop
   * @return True if property was set
   */
  bool Source::setLooping(bool loop)
  {
    alSourcei(m_sourceID, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
    return AudioUtil::CheckALError("set source looping");
  }

  /**
   * @brief Starts the source playing.
   * @return True on success
   */
  bool Source::play()
  {
    alSourcePlay(m_sourceID);
    return AudioUtil::CheckALError("source play");
  }

  /**
   * @brief Stops the source playing.
   * @return True on success
   */
  bool Source::stop()
  {
    alSourceStop(m_sourceID);
    return AudioUtil::CheckALError("source stop");
  }

  /**
   * @brief Tests if the source is currently playing.
   * @return True if playing
   */
  bool Source::isPlaying() const
  {
    ALint state;
    alGetSourcei(m_sourceID, AL_SOURCE_STATE, &state);
    return (state == AL_PLAYING);
  }

  /**
   * @copydoc SceneObject::update()
   */
  void Source::update(float msec, Subsystem sys)
  {
    SceneObject::update(msec, sys);

    if (sys == Subsystem::AUDIO)
    {
      m_listener->use();

      // Set position
      Vector4 position = m_worldTransform.positionVector();
      alSource3f(m_sourceID, AL_POSITION, position.x(), position.y(), position.z());
      AudioUtil::CheckALError("source position");

      // Set velocity
      // TODO: set this when physics engine is implemented
      alSource3f(m_sourceID, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
      AudioUtil::CheckALError("source velocity");
    }
  }
}
}
