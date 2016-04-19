/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "Listener.h"

#include <al.h>

#include <Engine_Maths/Vector3.h>
#include <Engine_Maths/Vector4.h>
#include <Engine_Maths/VectorOperations.h>

#include "AudioUtil.h"

using namespace Engine::Common;
using namespace Engine::Maths;

namespace Engine
{
namespace Audio
{
  /**
   * @copydoc SceneObject::SceneObject()
   */
  Listener::Listener(const std::string &name)
      : SceneObject(name)
  {
  }

  Listener::~Listener()
  {
  }

  /**
   * @brief Use this listener to output a sound to.
   */
  void Listener::use()
  {
    // Set position
    Vector4 position = m_worldTransform.positionVector();
    alListener3f(AL_POSITION, position.x(), position.y(), position.z());
    AudioUtil::CheckALError("listener position");

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
