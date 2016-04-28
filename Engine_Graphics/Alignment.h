/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_ALIGNMENT_H_
#define _ENGINE_GRAPHICS_ALIGNMENT_H_

#include <Engine_Utility/EnumClassBitset.h>

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Alignment options.
   * @author Dan Nixon
   */
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

  /**
   * @brief Bitset used for defining alignment options.
   */
  typedef Engine::Utility::EnumClassBitset<Alignment> Alignment_bitset;

  Alignment_bitset GetAlignment(Alignment a, Alignment b);
}
}

#endif
