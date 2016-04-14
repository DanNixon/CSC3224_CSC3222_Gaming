/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_LOGGING_FILEOUTPUTCHANNEL_H_
#define _ENGINE_LOGGING_FILEOUTPUTCHANNEL_H_

#include "IOutputChannel.h"

#include <fstream>

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
    FileOutputChannel(const std::string &filename);
    virtual ~FileOutputChannel();

    virtual bool open();
    virtual bool close();
    virtual void sendMessage(LogLevel level, const std::string &message);

  private:
    const std::string m_filename; //!< Log filename
    std::ofstream m_stream;       //!< Output file stream
  };
}
}

#endif
