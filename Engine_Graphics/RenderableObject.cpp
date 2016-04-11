/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "RenderableObject.h"

#include <Engine_Common/Subsystem.h>
#include <Engine_Maths/Matrix3.h>

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
   * @param transparent Flag indicating transparency
   */
  RenderableObject::RenderableObject(const std::string &name, Mesh *m, ShaderProgram *s, Texture *t, bool transparent)
      : SceneObject(name)
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
    if (sys == Subsystem::GRAPHICS && m_active && m_mesh && m_shaderProgram)
    {
      if (m_transparent && m_graphicalScene)
        m_graphicalScene->m_transparent.push_back(this);
      else
        render();
    }

    SceneObject::update(msec, sys);
  }

  /**
   * @brief Renders this object.
   */
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

    if (m_texture != nullptr)
      m_texture->use(program, 0);

    m_mesh->draw(program);

    glBindTexture(GL_TEXTURE_2D, 0);
  }

  /**
   * @copydoc SceneObject::addToScene()
   */
  void RenderableObject::addToScene(Scene *scene)
  {
    SceneObject::addToScene(scene);
    m_graphicalScene = dynamic_cast<GraphicalScene *>(scene);
  }
}
}
