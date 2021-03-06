/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_TEXTURE_H_
#define _ENGINE_GRAPHICS_TEXTURE_H_

#include <string>

#include <GL/glew.h>
#include <SDL_ttf.h>
#include <SOIL/SOIL.h>

#include <Engine_Maths/Vector2.h>
#include <Engine_Maths/Vector4.h>
#include <Engine_ResourceManagment/IMemoryManaged.h>
#include <Engine_ResourceManagment/ResourceLookup.h>

#include "Colour.h"

namespace Engine
{
namespace Graphics
{
  /**
   * @typedef TTFFontLookup
   * @brief TTF font resource lookup.
   */
  typedef Engine::ResourceManagment::ResourceLookup<TTF_Font *> TTFFontLookup;

  /**
   * @brief Defines the modes that can be used to render text.
   */
  enum class TextMode
  {
    BLENDED,
    SHADED
  };

  /**
   * @class Texture
   * @brief Encapsulates a GL texture and image loading.
   * @author Dan Nixon
   */
  class Texture : public Engine::ResourceManagment::IMemoryManaged
  {
  public:
    Texture(const std::string &name = "tex");
    virtual ~Texture();

    bool load(const std::string &filename);
    size_t text(const std::string &text, TTF_Font *font, const Colour &fgColour = Colour(),
                TextMode mode = TextMode::BLENDED, const Colour &bgColour = Colour(0.0f, 0.0f, 0.0f, 1.0f));

    bool valid() const;
    void use(GLuint shaderProgram, int idx) const;

    /**
     * @brief Gets the GL texture for use in rendering.
     * @return GL texture
     */
    inline GLuint texture() const
    {
      return m_texture;
    }

    /**
     * @brief Gets the dimensions of the texture image.
     * @return Texture dimensions
     */
    inline Engine::Maths::Vector2 dimensions() const
    {
      return m_size;
    }

  private:
    std::string m_name; //!< Name of texture
    GLuint m_texture;   //!< GL texture

    SDL_Surface *m_sdlSurface;

    Engine::Maths::Vector2 m_size; //!< Dimensions of texture
  };

  /**
   * @typedef TextureLookup
   * @brief Texture resource lookup.
   */
  typedef Engine::ResourceManagment::ResourceLookup<Texture *> TextureLookup;
}
}

#endif
