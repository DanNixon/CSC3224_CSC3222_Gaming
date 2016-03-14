/**
 * @file
 * @author Dan Nixon
 */

#include "WAVSource.h"

#include <alut.h>

namespace Engine
{
namespace Audio
{
  /**
   * @copydoc Source::Source()
   */
  WAVSource::WAVSource(const std::string &name, Listener *listener)
      : Source(name, listener)
  {
  }

  WAVSource::~WAVSource()
  {
  }

  /**
   * @brief Loads a WAV file.
   * @param filename File to load
   * @return True if file was successfully loaded
   */
  bool WAVSource::load(const std::string &filename)
  {
    // Delete the buffer created by the constructor
    if (m_buffer)
    {
      alSourcei(m_sourceID, AL_BUFFER, NULL);
      alDeleteBuffers(1, &m_buffer);
    }

    // Create a new buffer form the audio file
    m_buffer = alutCreateBufferFromFile(filename.c_str());
    alSourcei(m_sourceID, AL_BUFFER, m_buffer);

    return (alutGetError() == ALUT_ERROR_NO_ERROR);
  }
}
}
