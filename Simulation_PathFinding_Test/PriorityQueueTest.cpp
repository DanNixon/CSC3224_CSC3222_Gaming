/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "CppUnitTest.h"

#include <Simulation_PathFinding/NodePriorityQueue.h>
#include <Simulation_PathFinding/QueueableNode.h>

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Engine::Maths;

// clang-format off
namespace Simulation
{
namespace PathFinding
{
namespace Test
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(PriorityQueueTest)
{
public:
  TEST_METHOD(PriorityQueue_Pred)
  {
    Node * n1 = new Node("n1", Vector3());
    Node * n2 = new Node("n2", Vector3());

    QueueableNode * qn1 = new QueueableNode(n1);
    QueueableNode * qn2 = new QueueableNode(n2);

    qn1->fScore = 10;
    qn2->fScore = 5;

    auto pred = greater_ptr<QueueableNode>();

    Assert::IsTrue(pred(qn1, qn2));
    Assert::IsFalse(pred(qn2, qn1));
  }

  TEST_METHOD(PriorityQueue_PriorityOrder)
  {
    Node * n1 = new Node("n1", Vector3());
    Node * n2 = new Node("n2", Vector3());
    Node * n3 = new Node("n3", Vector3());

    QueueableNode * qn1 = new QueueableNode(n1);
    QueueableNode * qn2 = new QueueableNode(n2);
    QueueableNode * qn3 = new QueueableNode(n3);

    qn1->fScore = 10;
    qn2->fScore = 5;
    qn3->fScore = 20;

    NodePriorityQueue q;
    q.push(qn1);
    q.push(qn2);
    q.push(qn3);

    Assert::IsTrue(q.top() == qn2);
    q.pop();
    Assert::IsTrue(q.top() == qn1);
    q.pop();
    Assert::IsTrue(q.top() == qn3);
  }

  TEST_METHOD(PriorityQueue_ModifyFScore)
  {
    Node * n1 = new Node("n1", Vector3());
    Node * n2 = new Node("n2", Vector3());
    Node * n3 = new Node("n3", Vector3());

    QueueableNode * qn1 = new QueueableNode(n1);
    QueueableNode * qn2 = new QueueableNode(n2);
    QueueableNode * qn3 = new QueueableNode(n3);

    qn1->fScore = 10.0f;
    qn2->fScore = 5.0f;
    qn3->fScore = 20.0f;

    NodePriorityQueue q;
    q.push(qn1);
    q.push(qn2);
    q.push(qn3);

    qn3->fScore = 2.0f;

    Assert::IsTrue(q.top() == qn3);
    q.pop();
    Assert::IsTrue(q.top() == qn2);
    q.pop();
    Assert::IsTrue(q.top() == qn1);
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
