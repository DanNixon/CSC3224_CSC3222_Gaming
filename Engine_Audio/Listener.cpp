/**
 * @file
 * @author Dan Nixon
 */

#include "Listener.h"

#include <al.h>

#include <Vector3.h>
#include <Vector4.h>
#include <VectorOperations.h>

#include "AudioUtil.h"

using namespace Engine::Common;
using namespace Engine::Maths;

namespace Engine
{
  namespace Audio
  {
    Listener::Listener(const std::string &name)
      : SceneObject(name)
    {
    }

    Listener::~Listener()
    {
    }

    void Listener::use()
    {
      // Set position
      Vector4 position = m_worldTransform.positionVector();
      alListener3f(AL_POSITION, position.x(), position.y(), position.z());
      AudioUtil::CheckALError("listener position");

      // Set velocity
      // TODO: set this when physics engine is implemented
      alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
      AudioUtil::CheckALError("listener velocity");

      // Set orientation
      Vector3 facing = m_worldTransform.facingVector();
      VectorOperations::Normalise(facing);

      Vector3 up = m_worldTransform.facingVector();
      VectorOperations::Normalise(up);

      float orientation[] = {facing.x(), facing.y(), facing.z(), up.x(), up.y(), up.z()};

      alListenerfv(AL_ORIENTATION, orientation);
      AudioUtil::CheckALError("listener orientation");
    }
  }
}