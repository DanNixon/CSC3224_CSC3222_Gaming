/**
 * @file
 * @author Dan Nixon
 */

#include "RenderableObject.h"

#include <Matrix3.h>
#include <Subsystem.h>

using namespace Engine::Common;
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
  RenderableObject::RenderableObject(const std::string &name, Mesh *m, ShaderProgram *s, Texture *t, bool transparent)
      : SceneObject(name)
      , m_draw(true)
      , m_transparent(transparent)
      , m_mesh(m)
      , m_shaderProgram(s)
      , m_texture(t)
  {
  }

  RenderableObject::~RenderableObject()
  {
  }

  /**
   * @copydoc SceneObject::update()
   */
  void RenderableObject::update(float msec, Subsystem sys)
  {
    if (sys == Subsystem::GRAPHICS && m_draw && m_mesh && m_shaderProgram)
    {
      if (m_transparent && m_graphicalScene)
        m_graphicalScene->m_transparent.push_back(this);
      else
        render();
    }

    SceneObject::update(msec, sys);
  }

  void RenderableObject::render()
  {
    GLuint program = m_shaderProgram->program();

    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false, (float *)&m_worldTransform);
    glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false, (float *)&(m_scene->viewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, false, (float *)&(m_scene->projectionMatrix()));

    Matrix3 rotation = Matrix3(m_scene->viewMatrix());
    Vector3 invCamPos = m_scene->viewMatrix().positionVector();
    Vector3 camPos = rotation * -invCamPos;
    glUniform3fv(glGetUniformLocation(program, "cameraPos"), 1, (float *)&camPos);

    if (m_texture != NULL)
      m_texture->use(program, 0);

    m_mesh->draw();

    glBindTexture(GL_TEXTURE_2D, 0);
  }

  void RenderableObject::addToScene(Scene *scene)
  {
    SceneObject::addToScene(scene);
    m_graphicalScene = dynamic_cast<GraphicalScene *>(scene);
  }
}
}
