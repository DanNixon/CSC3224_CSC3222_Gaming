/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "FileOutputChannel.h"

namespace Engine
{
namespace Logging
{
  /**
   * @brief Creates a new file output log stream.
   * @param filename Log filename
   */
  FileOutputChannel::FileOutputChannel(const std::string &filename)
      : m_filename(filename)
      , m_stream()
  {
  }

  FileOutputChannel::~FileOutputChannel()
  {
  }

  /**
   * @copydoc IOutputChannel::open
   */
  bool FileOutputChannel::open()
  {
    // Open stream
    m_stream.open(m_filename, std::ios_base::app);
    bool result = m_stream.is_open();

    // Mark start of current session
    if (result)
      m_stream << "===== Log file opened." << std::endl;

    return result;
  }

  /**
   * @copydoc IOutputChannel::close
   */
  bool FileOutputChannel::close()
  {
    // Mark end of current session
    if (m_stream.is_open())
      m_stream << "===== Log file closed." << std::endl;

    // Close stream
    m_stream.close();
    return !m_stream.is_open();
  }

  /**
   * @copydoc IOutputChannel::sendMessage
   */
  void FileOutputChannel::sendMessage(LogLevel level, const std::string &message)
  {
    if (level >= m_level)
      m_stream << message << std::endl;
  }
}
}