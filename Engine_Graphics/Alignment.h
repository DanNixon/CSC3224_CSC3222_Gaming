/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_ALIGNMENT_H_
#define _ENGINE_GRAPHICS_ALIGNMENT_H_

#include <SDL/SDL.h>

#include <EnumClassBitset.h>

namespace Engine
{
namespace Graphics
{
  enum class Alignment : size_t
  {
    X_LEFT,
    X_CENTRE,
    X_RIGHT,

    Y_TOP,
    Y_CENTRE,
    Y_BOTTOM,

    Z_NEAR,
    Z_CENTRE,
    Z_FAR,

    MAX_VALUE
  };

  typedef Engine::Utility::EnumClassBitset<Alignment> Alignment_bitset;
}
}

#endif