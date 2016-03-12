/**
 * @file
 * @author Dan Nixon
 */

#include "Source.h"

#include <Vector4.h>

#include "AudioUtil.h"

using namespace Engine::Maths;

namespace Engine
{
namespace Audio
{
  Source::Source(const std::string &name, Listener *listener)
      : SceneObject(name)
      , m_listener(listener)
  {
    alGenSources(1, &m_sourceID);
    alGenBuffers(1, &m_buffer);

    alSourcei(m_sourceID, AL_BUFFER, m_buffer);

    alSourcef(m_sourceID, AL_PITCH, 1);
    alSourcef(m_sourceID, AL_GAIN, 1);

    setLooping(false);
  }

  Source::~Source()
  {
    alSourcei(m_sourceID, AL_BUFFER, NULL);

    alDeleteSources(1, &m_sourceID);
    alDeleteBuffers(1, &m_buffer);
  }

  bool Source::valid() const
  {
    return (m_sourceID > 0 && m_buffer > 0 && m_listener);
  }

  bool Source::setLooping(bool loop)
  {
    alSourcei(m_sourceID, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
    return AudioUtil::CheckALError("set source looping");
  }

  bool Source::play()
  {
    alSourcePlay(m_sourceID);
    return AudioUtil::CheckALError("source play");
  }

  bool Source::stop()
  {
    alSourceStop(m_sourceID);
    return AudioUtil::CheckALError("source stop");
  }

  bool Source::isPlaying() const
  {
    ALint state;
    alGetSourcei(m_sourceID, AL_SOURCE_STATE, &state);
    return (state == AL_PLAYING);
  }

  void Source::update(float msec)
  {
    SceneObject::update(msec);

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