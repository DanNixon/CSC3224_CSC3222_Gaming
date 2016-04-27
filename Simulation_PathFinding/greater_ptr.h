/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_PATHFINDING_GREATERPTR_H_
#define _SIMULATION_PATHFINDING_GREATERPTR_H_

#include <functional>

/**
 * @struct greater_ptr
 * @brief Used to perform comparison between pointers to objects.
 * @see http://forums.codeguru.com/showthread.php?337599&p=1137606#post1137606
 */
template <typename T> struct greater_ptr : std::binary_function<bool, const T *, const T *>
{
  const bool operator()(const T *a, const T *b) const
  {
    if (a == nullptr)
      // if b is also 0, then they are equal, hence a is not < than b
      return b != nullptr;
    else if (b == nullptr)
      return false;
    else
      return (*a) > (*b);
  }
};

#endif
