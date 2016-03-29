/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_SNOOKER_TABLE_H_
#define _SIMULATION_SNOOKER_TABLE_H_

#include <Engine_Graphics/RenderableObject.h>

#include <Engine_Maths/Vector2.h>

#include "Cushion.h"
#include "Pocket.h"

namespace Simulation
{
namespace Snooker
{
  /**
   * @class Table
   * @brief Represents a snooker table.
   * @author Dan Nixon
   */
  class Table : public Engine::Graphics::RenderableObject
  {
  public:
    /**
     * @var NUM_CUSHIONS
     * @brief Number of cushions on the table.
     */
    static const int NUM_CUSHIONS = 4;

    /**
     * @var NUM_POCKETS
     * @brief Number of pockets on the table.
     */
    static const int NUM_POCKETS = 6;

    static const Engine::Maths::Vector2 DIMENSIONS;
    static const Engine::Maths::Vector2 HALF_DIMENSIONS;

    static const Engine::Maths::Vector2 PLAY_AREA;
    static const Engine::Maths::Vector2 HALF_PLAY_AREA;

    Table(Simulation::Physics::Entity::EntityPtrList &entityList);
    virtual ~Table();

    /**
     * @brief Gets a cushion.
     * @param idx Cushion index
     * @return Cushion
     */
    Cushion *cushion(size_t idx)
    {
      if (idx > NUM_CUSHIONS)
        return NULL;

      return m_cushions[idx];
    }

    /**
     * @brief Gets a pocket.
     * @param idx Pocket index
     * @return Pocket
     */
    Pocket *pocket(size_t idx)
    {
      if (idx > NUM_POCKETS)
        return NULL;

      return m_pockets[idx];
    }

  private:
    Cushion *m_cushions[4]; //!< Side cushions
    Pocket *m_pockets[6];   //!< Pockets
  };
}
}

#endif