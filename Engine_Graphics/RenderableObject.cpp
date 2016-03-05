/**
 * @file
 * @author Dan Nixon
 */

#include "RenderableObject.h"

#include "Matrix3.h"

using namespace Engine::Maths;

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Creates a new renderable object with a given mesh, shader and
   * texture.
   * @param name Name of the obejct
   * @param m Mesh
   * @param s Shader
   * @param t Texture
   */
  RenderableObject::RenderableObject(const std::string &name, Mesh *m,
                                     ShaderProgram *s, Texture *t)
      : SceneObject(name)
      , m_mesh(m)
      , m_shaderProgram(s)
      , m_texture(t)
  {
  }

  RenderableObject::~RenderableObject()
  {
    if (m_mesh != NULL)
      delete m_mesh;

    //  if (m_shaderProgram != NULL)
    //    delete m_shaderProgram;
  }

  /**
   * @copydoc SceneObject::render
   */
  void RenderableObject::render()
  {
    if (m_mesh && m_shaderProgram)
    {
      GLuint program = m_shaderProgram->program();

      glUseProgram(program);
      glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false,
                         (float *)&m_worldTransform);
      glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false,
                         (float *)&(m_scene->viewMatrix()));
      glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, false,
                         (float *)&(m_scene->projectionMatrix()));

      Matrix3 rotation = Matrix3(m_scene->viewMatrix());
      Vector3 invCamPos = m_scene->viewMatrix().positionVector();
      Vector3 camPos = rotation * -invCamPos;
      glUniform3fv(glGetUniformLocation(program, "cameraPos"), 1,
                   (float *)&camPos);

      if (m_texture != NULL)
        m_texture->use(program, 0);

      m_mesh->draw();

      glBindTexture(GL_TEXTURE_2D, 0);
    }

    SceneObject::render();
  }
}
}
