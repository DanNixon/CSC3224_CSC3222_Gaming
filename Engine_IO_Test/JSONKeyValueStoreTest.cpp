/**
 * @file
 * @author Dan Nixon
 */

#include "CppUnitTest.h"

#include <JSONKeyValueStore.h>
#include <KVNode.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
namespace IO
{
namespace Test
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(JSONKeyValueStoreTest)
{
public:
  TEST_METHOD(test_LoadJSONFromStream)
  {
    // Sample JSON string
    std::stringstream stream;
    // TODO

    // Parse
    JSONKeyValueStore store;
    Assert::IsTrue(store.load(stream));

    KVNode & root = store.root();

    // TODO
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
