/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "Aircraft.h"

#include <sstream>

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

  std::string Aircraft::modelFilename(AircraftModel model) const
  {
    std::stringstream str;
    str << m_name << "/";

    switch (model)
    {
    case AircraftModel::BODY:
      str << m_name;
      break;
    case AircraftModel::MAIN_ROTOR_SPIN:
      str << "Mainrotor";
      break;
    case AircraftModel::TAIL_ROTOR_SPIN:
      str << "Tailrotor";
      break;
    }

    str << ".obj";

    return str.str();
  }

  std::string Aircraft::audioFilename(AircraftSound sound) const
  {
    std::stringstream str;
    str << m_name << "/";

    switch (sound)
    {
    case AircraftSound::ENGINE_IDLE:
      str << m_name;
      break;
    case AircraftSound::MAIN_ROTOR:
      str << "blade";
      break;
    case AircraftSound::TAIL_ROTOR:
      str << "tail";
      break;
    case AircraftSound::CRASH:
      str << ""; // TODO
      break;
    }

    str << ".wav";

    return str.str();
  }
}
}