/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_GRAPHICALPATHFINDER_VIEWMODE_H_
#define _SIMULATION_GRAPHICALPATHFINDER_VIEWMODE_H_

#include <Engine_Utility/EnumClassBitset.h>

namespace Simulation
{
namespace GraphicalPathFinder
{
  /**
   * @brief View mode options.
   * @author Dan Nixon
   */
  enum class ViewMode : size_t
  {
    WEIGHTS,
    OPEN_LIST,
    CLOSED_LIST,
    PATH,

    MAX_VALUE
  };

  /**
   * @brief Bitset used for defining view options.
   */
  typedef Engine::Utility::EnumClassBitset<ViewMode> ViewMode_bitset;
}
}

#endif
