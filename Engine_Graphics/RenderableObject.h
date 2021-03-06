/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_RENDERABLEOBJECT_H_
#define _ENGINE_GRAPHICS_RENDERABLEOBJECT_H_

#include <Engine_Common/SceneObject.h>

#include "GraphicalScene.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"

namespace Engine
{
namespace Graphics
{
  /**
   * @class RenderableObject
   * @brief Represents a renderable item in a Scene.
   * @author Dan Nixon
   */
  class RenderableObject : public Engine::Common::SceneObject
  {
  public:
    RenderableObject(const std::string &name, Mesh *m = nullptr, ShaderProgram *s = nullptr, Texture *t = nullptr,
                     bool transparent = false);
    ~RenderableObject();

    void setTransparent(bool transparent, size_t recursionLevels = 0, size_t depth = 0);

    /**
     * @brief Gets the transparency of this object.
     * @return Transparency
     */
    inline bool transparent() const
    {
      return m_transparent;
    }

    /**
     * @brief Sets the Mesh this object renders.
     * @param m Mesh
     * @see RenderableObject::mesh
     */
    void setMesh(Mesh *m)
    {
      m_mesh = m;
    }

    /**
     * @brief Gets the Mesh this object renders.
     * @return Mesh
     * @see RenderableObject::setMesh
     */
    inline Mesh *mesh() const
    {
      return m_mesh;
    }

    /**
     * @brief Sets the ShaderProgram this object uses to render.
     * @param s Shader program
     * @see RenderableObject::shader
     */
    void setShader(ShaderProgram *s)
    {
      m_shaderProgram = s;
    }

    /**
     * @brief Gets the ShaderProgram this object uses to render.
     * @return Shader program
     * @see RenderableObject::setShader
     */
    inline ShaderProgram *shader() const
    {
      return m_shaderProgram;
    }

    /**
     * @brief Sets the texture associated with this object.
     * @param tex Texture
     * @see RenderableObject::texture
     */
    void setTexture(Texture *tex)
    {
      m_texture = tex;
    }

    /**
     * @brief Gets the texture associated with this object.
     * @return Texture
     * @see RenderableObject::setTexture
     */
    inline Texture *texture() const
    {
      return m_texture;
    }

    virtual void update(float msec, Engine::Common::Subsystem sys);
    void render();

  protected:
    virtual void draw(GLuint program);
    virtual void addToScene(Engine::Common::Scene *scene);

  protected:
    GraphicalScene *m_graphicalScene; //!< Graphical scene object is part of
    bool m_transparent;               //!< Flag indicating transparency of this object
    Mesh *m_mesh;                     //!< Mesh represented by this object
    ShaderProgram *m_shaderProgram;   //!< Shader used to render m_mesh
    Texture *m_texture;               //!< Texture used on m_mesh
  };
}
}

#endif
