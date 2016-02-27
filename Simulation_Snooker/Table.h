/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include "Cushion.h"
#include <RenderableObject.h>
#include <Vector2.h>

/**
 * @class Table
 * @brief Represents a snooker table.
 * @author Dan Nixon
 */
class Table : public Engine::Graphics::RenderableObject
{
public:
  static const Engine::Maths::Vector2 DIMENSIONS;
  static const Engine::Maths::Vector2 HALF_DIMENSIONS;

  Table();
  virtual ~Table();

  /**
   * @brief Gets a cushion.
   * @param idx Cushion index
   * @return Cushion
   */
  Cushion *cushion(size_t idx)
  {
    return m_cushions[idx];
  }

private:
  Cushion *m_cushions[4]; //!< Side cushions
};
