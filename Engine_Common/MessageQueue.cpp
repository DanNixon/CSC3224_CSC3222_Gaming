/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "MessageQueue.h"

namespace Engine
{
namespace Common
{
  /**
   * @brief Create a new message queue.
   */
  MessageQueue::MessageQueue()
  {
  }

  MessageQueue::~MessageQueue()
  {
  }

  /**
   * @brief Returns the next message on the queue for a given subsystem.
   * @param sys Target subsystem
   * @return Next message
   */
  MessageQueue::MessageType MessageQueue::peek(Subsystem sys) const
  {
    // TODO
    return MessageQueue::MessageType();
  }

  /**
   * @brief Returns the next message on the queue for a given subsystem and
   *        removes it from the queue.
   * @param sys Target subsystem
   * @return Next message
   */
  MessageQueue::MessageType MessageQueue::pop(Subsystem sys)
  {
    // TODO
    return MessageQueue::MessageType();
  }

  /**
   * @brief Returns the number of messages on the queue for a given subsystem.
   * @param sys Target subsystem
   * @return NUmber of messages in queue
   */
  size_t MessageQueue::numMessages(Subsystem sys) const
  {
    // TODO
    return 0;
  }
}
}
