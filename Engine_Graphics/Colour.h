/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_COLOUR_H_
#define _ENGINE_GRAPHICS_COLOUR_H_

#include <SDL/SDL.h>
#include <assimp/color4.h>

#include <Engine_Maths/Vector4.h>

namespace Engine
{
namespace Graphics
{
  /**
   * @class Colour
   * @brief Wrapper around a Vector4 for holding colours.
   * @author Dan Nixon
   */
  class Colour : public Engine::Maths::Vector4
  {
  public:
    /**
     * @brief Creates a new colour with specified values.
     * @param r Red channel intensity
     * @param g Green channel intensity
     * @param b Blue channel intensity
     * @param a Alpha channel intensity
     */
    Colour(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f)
        : Vector4(r, g, b, a)
    {
    }

    /**
     * @brief Creates a new colour from an Assimp 4D colour.
     * @param col Assimp colour
     */
    Colour(const aiColor4D &col)
        : Vector4(col.r, col.g, col.b, col.a)
    {
    }

    /**
     * @brief Converts this colour to an SDL colour.
     * @return Colour as SDL colour
     */
    SDL_Color sdlColour() const
    {
      SDL_Color c;
      c.r = (Uint8)(255.0f * m_x);
      c.g = (Uint8)(255.0f * m_y);
      c.b = (Uint8)(255.0f * m_z);
      c.a = (Uint8)(255.0f * m_w);
      return c;
    }
  };
}
}

#endif
