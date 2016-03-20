/**
* @file
* @author Dan Nixon
*/

#include "Texture.h"

using namespace Engine::Maths;

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
  void Texture::text(const std::string &text, TTF_Font *font, const Colour &fgColour, TextMode mode,
                     const Colour &bgColour)
  {
    if (m_texture != 0)
      glDeleteTextures(1, &m_texture);

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    SDL_Surface *pallate;
    switch (mode)
    {
    case TextMode::SHADED:
    {
      pallate = TTF_RenderText_Shaded(font, text.c_str(), fgColour.sdlColour(), bgColour.sdlColour());
      break;
    }
    default:
      pallate = TTF_RenderText_Blended(font, text.c_str(), fgColour.sdlColour());
    }

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

    SDL_Surface *img = SDL_CreateRGBSurface(0, pallate->w, pallate->h, 32, rmask, gmask, bmask, amask);
    SDL_BlitSurface(pallate, NULL, img, NULL);
    SDL_FreeSurface(pallate);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);

    GLenum error = glGetError();
    bool good = error == GL_NO_ERROR;

    m_size = Vector2((float)img->w, (float)img->h);

    glBindTexture(GL_TEXTURE_2D, 0);
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
