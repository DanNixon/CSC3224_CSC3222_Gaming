/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "Aircraft.h"

#include <Engine_Logging/Logger.h>

using namespace Engine::Common;

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

namespace GameDev
{
namespace Demo
{
  Aircraft::Aircraft(const std::string &name)
      : SceneObject(name)
  {
  }

  Aircraft::~Aircraft()
  {
  }
}
}