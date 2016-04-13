/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_LOGGING_FILEOUTPUTCHANNEL_H_
#define _ENGINE_LOGGING_FILEOUTPUTCHANNEL_H_

#include "IOutputChannel.h"

namespace Engine
{
namespace Logging
{
  /**
   * @class FileOutputChannel
   * @brief Output channel for saving logs to a file.
   * @author Dan Nixon
   */
  class FileOutputChannel : public IOutputChannel
  {
  public:
    FileOutputChannel()
    {
    }

    virtual ~FileOutputChannel()
    {
    }

    /**
     * @copydoc IOutputChannel::open
     */
    virtual bool open()
    {
      // TODO
    }

    /**
     * @copydoc IOutputChannel::close
     */
    virtual bool close()
    {
      // TODO
    }

    /**
     * @copydoc IOutputChannel::sendMessage
     */
    virtual void sendMessage(LogLevel level, const std::string &message)
    {
      if (level >= m_level)
      {
        // TODO
      }
    }
  };
}
}

#endif
