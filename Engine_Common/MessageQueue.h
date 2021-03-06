/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _ENGINE_COMMON_MESSAGEQUEUE_H_
#define _ENGINE_COMMON_MESSAGEQUEUE_H_

#include <vector>

#include "Subsystem.h"

namespace Engine
{
namespace Common
{
  /**
   * @class MessageQueue
   * @brief Used for queueing messages to be passeed between subsystems.
   * @author Dan Nixon
   */
  class MessageQueue
  {
  public:
    /**
     * @typedef MessageType
     * @brief Represents a message as a pair of (destination subsystem,
     *        string).
     */
    typedef std::pair<Subsystem, std::string> MessageType;

    /**
     * @typedef MessageList
     * @brief Underlying storage type for MessageQueue.
     */
    typedef std::vector<MessageType> MessageList;

  public:
    MessageQueue();
    virtual ~MessageQueue();

    /**
     * @brief Pushes a new message to the queue.
     * @param msg New message
     */
    inline void push(MessageType msg)
    {
      m_queue.push_back(msg);
    }

    MessageType peek(Subsystem sys) const;
    MessageType pop(Subsystem sys);

    size_t numMessages(Subsystem sys = Subsystem::ALL) const;
    bool hasMessage(Subsystem sys = Subsystem::ALL) const;

  private:
    MessageList::iterator first(Subsystem sys);
    MessageList::const_iterator cfirst(Subsystem sys) const;

  private:
    MessageList m_queue; //!< Queued messages
  };
}
}

#endif
