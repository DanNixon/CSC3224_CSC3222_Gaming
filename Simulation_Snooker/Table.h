/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATIONSNOOKER_TABLE_H_
#define _SIMULATIONSNOOKER_TABLE_H_

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

  static const Engine::Maths::Vector2 PLAY_AREA;
  static const Engine::Maths::Vector2 HALF_PLAY_AREA;

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

#endif