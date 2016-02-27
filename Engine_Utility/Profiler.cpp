/**
 * @file
 * @author Dan Nixon
 */

#include "Profiler.h"

using namespace Engine::Common;

namespace Engine
{
namespace Utility
{
  Profiler::Profiler(Game * target)
    : m_target(target)
  {
  }

  Profiler::~Profiler()
  {
  }

  void Profiler::computeStats(Uint32 dtMilliSec)
  {
    // TODO
  }
}
}