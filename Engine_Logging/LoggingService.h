/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_LOGGING_LOGGINGSERVICE_H_
#define _ENGINE_LOGGING_LOGGINGSERVICE_H_

#include <string>
#include <vector>

#include "IOutputChannel.h"
#include "LogLevel.h"

namespace Engine
{
namespace Logging
{
  /**
   * @class LoggingService
   * @brief Singleton used for receiving log calls and routing messages to each
   *        output channel.
   * @author Dan Nixon
   */
  class LoggingService
  {
  public:
    /**
     * @brief Gets a reference to the instance of the LoggingService.
     * @return LoggingService instance
     */
    static LoggingService &Instance()
    {
      static LoggingService instance;
      return instance;
    }

    /**
     * @brief No copy constructor
     */
    LoggingService(LoggingService const &) = delete;

    /**
     * @brief No move constructor
     */
    LoggingService(LoggingService &&) = delete;

    /**
     * @brief No assign copy constructor
     */
    LoggingService &operator=(LoggingService const &) = delete;

    /**
     * @brief No assign move constructor
     */
    LoggingService &operator=(LoggingService &&) = delete;

    void shutdown();

    void addOutput(IOutputChannel *output);
    void removeOutput(IOutputChannel *output);

  protected:
    LoggingService();
    ~LoggingService();

  private:
    friend class Logger;
    void log(LogLevel level, const std::string &loggerName, const std::string &message);

  private:
    std::vector<IOutputChannel *> m_outputs; //!< Output channels
  };
}
}

#endif
