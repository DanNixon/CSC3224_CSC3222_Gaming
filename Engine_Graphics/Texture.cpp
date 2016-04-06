/**
* @file
* @author Dan Nixon
*/

#include "Texture.h"

#include <algorithm>

#include <Engine_Utility/StringUtils.h>

using namespace Engine::Maths;
using namespace Engine::Utility;

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Creates a new texture with a given name.
   * @param name Texture name (defaults to "tex")
   *
   * Texture name is used as the uniform name for use in shaders.
   */
  Texture::Texture(const std::string &name)
      : m_name(name)
      , m_texture(0)
      , m_size(0.0f, 0.0f)
  {
  }

  Texture::~Texture()
  {
    glDeleteTextures(1, &m_texture);

    if (m_sdlSurface)
      SDL_FreeSurface(m_sdlSurface);
  }

  /**
   * @brief Loads an image file into a GL texture.
   * @param filename Image file to load
   * @return GL texture, 0 if loading failed
   */
  bool Texture::load(const std::string &filename)
  {
    m_texture = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    return (m_texture != 0);
  }

  /**
   * @brief Generates a texture with text.
   * @param text Text to display
   * @param font Font to display with
   * @param fgColour Text colour
   * @param mode Rendering mode
   * @param bgColour Background colour
   * @return GL texture, 0 if loading/generation failed
   */
  size_t Texture::text(const std::string &text, TTF_Font *font, const Colour &fgColour, TextMode mode,
                       const Colour &bgColour)
  {
    // Free old texture
    if (m_texture != 0)
      glDeleteTextures(1, &m_texture);
    if (m_sdlSurface)
      SDL_FreeSurface(m_sdlSurface);

    // Generate new GL texture
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Split text into lines
    std::vector<std::string> subStrings = StringUtils::Split(text, '\n');

    // Rasterise each line
    std::vector<SDL_Surface *> textSurfaces;
    float totalHeight = 0.0f;
    float maxWidth = 0.0f;

    for (auto it = subStrings.begin(); it != subStrings.end(); ++it)
    {
      SDL_Surface *pallate;
      switch (mode)
      {
      case TextMode::SHADED:
        pallate = TTF_RenderText_Shaded(font, it->c_str(), fgColour.sdlColour(), bgColour.sdlColour());
        break;
      default:
        pallate = TTF_RenderText_Blended(font, it->c_str(), fgColour.sdlColour());
      }

      totalHeight += (float)pallate->h;
      maxWidth = std::max(maxWidth, (float)pallate->w);

      textSurfaces.push_back(pallate);
    }

    // Create new etxture surface
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    m_sdlSurface = SDL_CreateRGBSurface(0, maxWidth, totalHeight, 32, rmask, gmask, bmask, amask);

    // Blit each line surface to texture surface
    int currentHeight = 0;
    for (auto it = textSurfaces.begin(); it != textSurfaces.end(); ++it)
    {
      int i = it - textSurfaces.begin();

      // Destinaion box
      SDL_Rect destRect;
      destRect.h = (*it)->h;
      destRect.w = (*it)->w;
      destRect.x = 0;
      destRect.y = currentHeight;

      currentHeight += (*it)->h;

      // Blit to texture surface
      SDL_BlitSurface(*it, nullptr, m_sdlSurface, &destRect);
      SDL_FreeSurface(*it);
    }

    // Generate GL texture
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_sdlSurface->w, m_sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 m_sdlSurface->pixels);

    // Record size of texture
    m_size = Vector2((float)m_sdlSurface->w, (float)m_sdlSurface->h);

    glBindTexture(GL_TEXTURE_2D, 0);

    return subStrings.size();
  }

  /**
   * @brief Checks to see if a valid image has been loaded into the texture.
   * @return True if tecture holds a valid image
   */
  bool Texture::valid() const
  {
    return (m_texture > 0);
  }

  /**
   * @brief Use the texture in rendering.
   * @param shaderProgram Shader program used in rendering
   * @param idx Index of this testure in rendering
   */
  void Texture::use(GLuint shaderProgram, int idx) const
  {
    if (m_texture == 0)
      return;

    glUniform1i(glGetUniformLocation(shaderProgram, m_name.c_str()), idx);
    glActiveTexture(GL_TEXTURE0 + idx);
    glBindTexture(GL_TEXTURE_2D, m_texture);
  }
}
}
