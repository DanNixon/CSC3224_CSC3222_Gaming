/** @file */

#include "RenderableObject.h"

#include "Matrix3.h"

RenderableObject::RenderableObject()
    : m_mesh(NULL)
    , m_shader(NULL)
{
  for (int i = 0; i < NUM_TEXTURES; i++)
    m_textures[i] = NULL;
}

RenderableObject::RenderableObject(Mesh *m, Shader *s, GLuint t)
    : m_mesh(m)
    , m_shader(s)
{
  for (int i = 0; i < NUM_TEXTURES; i++)
    m_textures[i] = NULL;

  m_textures[0] = t;
}

RenderableObject::~RenderableObject()
{
  if (m_mesh != NULL)
    delete m_mesh;

  if (m_shader != NULL)
    delete m_shader;
}

void RenderableObject::render()
{
  if (m_mesh && m_shader)
  {
    GLuint program = m_shader->program();

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

    glUniform1i(glGetUniformLocation(program, "objectTextures[0]"), 0);
    glUniform1i(glGetUniformLocation(program, "objectTextures[1]"), 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textures[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_textures[1]);

    m_mesh->draw();
  }

  SceneObject::render();
}
