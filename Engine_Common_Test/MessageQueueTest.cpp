/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "CppUnitTest.h"

#include <Engine_Common/MessageQueue.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Engine::Common;

// clang-format off
namespace Engine
{
namespace IO
{
namespace Test
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(MessageQueueTest)
{
public:
  TEST_METHOD(MessageQueue_Test)
  {
    MessageQueue q;

    // Test messages
    MessageQueue::MessageType m1 = std::make_pair(Subsystem::GAME_LOGIC, "m1");
    MessageQueue::MessageType m2 = std::make_pair(Subsystem::AI, "m2");
    MessageQueue::MessageType m3 = std::make_pair(Subsystem::AI, "m3");
    MessageQueue::MessageType m4 = std::make_pair(Subsystem::GAME_LOGIC, "m4");
    MessageQueue::MessageType m5 = std::make_pair(Subsystem::AI, "m5");

    // Assert initial queue size
    Assert::AreEqual((size_t)0, q.numMessages());

    q.push(m1);
    Assert::AreEqual((size_t)1, q.numMessages());
    Assert::AreEqual((size_t)1, q.numMessages(Subsystem::GAME_LOGIC));
    Assert::AreEqual((size_t)0, q.numMessages(Subsystem::AI));

    Assert::AreEqual(std::string("m1"), q.peek(Subsystem::GAME_LOGIC).second);
    Assert::AreEqual(std::string(""), q.peek(Subsystem::AI).second);

    q.push(m2);
    Assert::AreEqual((size_t)2, q.numMessages());
    Assert::AreEqual((size_t)1, q.numMessages(Subsystem::GAME_LOGIC));
    Assert::AreEqual((size_t)1, q.numMessages(Subsystem::AI));

    Assert::AreEqual(std::string("m1"), q.peek(Subsystem::GAME_LOGIC).second);
    Assert::AreEqual(std::string("m2"), q.peek(Subsystem::AI).second);

    q.push(m3);
    Assert::AreEqual((size_t)3, q.numMessages());
    Assert::AreEqual((size_t)1, q.numMessages(Subsystem::GAME_LOGIC));
    Assert::AreEqual((size_t)2, q.numMessages(Subsystem::AI));

    Assert::AreEqual(std::string("m1"), q.pop(Subsystem::GAME_LOGIC).second);
    Assert::AreEqual(std::string("m2"), q.pop(Subsystem::AI).second);

    Assert::AreEqual((size_t)1, q.numMessages());
    Assert::AreEqual((size_t)0, q.numMessages(Subsystem::GAME_LOGIC));
    Assert::AreEqual((size_t)1, q.numMessages(Subsystem::AI));

    Assert::AreEqual(std::string(""), q.peek(Subsystem::GAME_LOGIC).second);
    Assert::AreEqual(std::string("m3"), q.peek(Subsystem::AI).second);
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
