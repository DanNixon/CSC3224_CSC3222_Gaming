/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_RENDERABLEOBJECT_H_
#define _ENGINE_GRAPHICS_RENDERABLEOBJECT_H_

#include "Mesh.h"
#include "SceneObject.h"
#include "ShaderProgram.h"
#include "Texture.h"

namespace Engine
{
namespace Graphics
{
  /**
   * @class RenderableObject
   * @brief Represents a renderable item in a Scene.
   */
  class RenderableObject : public Engine::Common::SceneObject
  {
  public:
    RenderableObject(const std::string &name, Mesh *m = NULL, ShaderProgram *s = NULL, Texture *t = NULL);
    ~RenderableObject();

    /**
     * @brief Sets the visibility of this object.
     * @param visible Visibility
     */
    void setVisible(bool visible)
    {
      m_draw = visible;
    }

    /**
     * @brief Gets the visibility of this object.
     * @return Visibility
     */
    inline bool visible() const
    {
      return m_draw;
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

    virtual void render();

  protected:
    bool m_draw;                    //!< Flag indicating if this object should be rendered
    Mesh *m_mesh;                   //!< Mesh represented by this object
    ShaderProgram *m_shaderProgram; //!< Shader used to render m_mesh
    Texture *m_texture;             //!< Texture used on m_mesh
  };
}
}

#endif
