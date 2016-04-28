/**
 * @file
 * @author Dan Nixon (120263697)
 */

#include "Alignment.h"

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Helper function for getting an Alignment bitset for a generic
   *        alignment.
   * @param a First alignment bit
   * @param b Second alignment bit
   * @return Alignment bitset
   */
  Alignment_bitset GetAlignment(Alignment a, Alignment b)
  {
    Alignment_bitset alignment;
    alignment.set(a);
    alignment.set(b);
    return alignment;
  }
}
}