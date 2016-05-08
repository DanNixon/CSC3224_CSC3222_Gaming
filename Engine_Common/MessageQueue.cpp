/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "MessageQueue.h"

#include <algorithm>

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
    auto it = cfirst(sys);

    // Return empty message if not found
    if (it == m_queue.end())
      return MessageQueue::MessageType();

    return *it;
  }

  /**
   * @brief Returns the next message on the queue for a given subsystem and
   *        removes it from the queue.
   * @param sys Target subsystem
   * @return Next message
   */
  MessageQueue::MessageType MessageQueue::pop(Subsystem sys)
  {
    auto it = first(sys);

    // Return empty message if not found
    if (it == m_queue.end())
      return MessageQueue::MessageType();

    // Record the messgae
    MessageQueue::MessageType msg = *it;

    // Remove message from queue
    m_queue.erase(it);

    return msg;
  }

  /**
   * @brief Returns the number of messages on the queue for a given subsystem.
   * @param sys Target subsystem
   * @return NUmber of messages in queue
   */
  size_t MessageQueue::numMessages(Subsystem sys) const
  {
    switch (sys)
    {
    case Subsystem::NONE:
      return 0;
    case Subsystem::ALL:
      return m_queue.size();
    default:
      return std::count_if(m_queue.begin(), m_queue.end(),
                           [sys](MessageQueue::MessageType m) { return m.first == sys; });
    }
  }

  /**
   * @brief Checks if there messages in the queue for a given subsystem.
   * @param sys Target subsystem
   * @return True f there are messages
   */
  bool MessageQueue::hasMessage(Subsystem sys) const
  {
    return cfirst(sys) != m_queue.end();
  }

  MessageQueue::MessageList::iterator MessageQueue::first(Subsystem sys)
  {
    if (sys == Subsystem::NONE)
      return m_queue.end();

    if (sys == Subsystem::ALL)
      return m_queue.begin();

    return std::find_if(m_queue.begin(), m_queue.end(), [sys](MessageQueue::MessageType m) { return m.first == sys; });
  }

  MessageQueue::MessageList::const_iterator MessageQueue::cfirst(Subsystem sys) const
  {
    if (sys == Subsystem::NONE)
      return m_queue.cend();

    if (sys == Subsystem::ALL)
      return m_queue.cbegin();

    return std::find_if(m_queue.begin(), m_queue.end(), [sys](MessageQueue::MessageType m) { return m.first == sys; });
  }
}
}
