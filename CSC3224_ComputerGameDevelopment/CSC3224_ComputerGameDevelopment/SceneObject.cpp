#include "SceneObject.h"

#include "Matrix3.h"

SceneObject::SceneObject(void)
{
  for (int i = 0; i < NUM_TEXTURES; i++)
    textures[i] = NULL;

  mesh = NULL;
  shader = NULL;
  parent = NULL;
}

SceneObject::SceneObject(Mesh *m, Shader *s, GLuint t)
{
  for (int i = 0; i < NUM_TEXTURES; i++)
    textures[i] = NULL;

  mesh = m;
  shader = s;
  textures[0] = t;
  parent = NULL;
}

SceneObject::~SceneObject(void)
{
  if (mesh != NULL)
    delete mesh;

  if (shader != NULL)
    delete shader;

  if (parent != NULL)
    delete parent;
}

void SceneObject::Update(float msec)
{
  if (parent)
    worldTransform = parent->modelMatrix * modelMatrix;
  else
    worldTransform = modelMatrix;

  for (vector<SceneObject *>::const_iterator i = children.begin();
       i != children.end(); ++i)
    (*i)->Update(msec);
}

void SceneObject::render()
{
  Matrix4 modelMatrix = GetWorldTransform();

  if (shader && mesh)
  {
    GLuint program = shader->GetShaderProgram();

    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false,
                       (float *)&modelMatrix);
    glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false,
                       (float *)&(scene->viewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, false,
                       (float *)&(scene->projectionMatrix()));

    Matrix3 rotation = Matrix3(scene->viewMatrix());
    Vector3 invCamPos = scene->viewMatrix().GetPositionVector();
    Vector3 camPos = rotation * -invCamPos;
    glUniform3fv(glGetUniformLocation(program, "cameraPos"), 1,
                 (float *)&camPos);

    glUniform1i(glGetUniformLocation(program, "objectTextures[0]"), 0);
    glUniform1i(glGetUniformLocation(program, "objectTextures[1]"), 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, GetTexture(0));
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, GetTexture(1));

    mesh->Draw();
  }

  for (vector<SceneObject *>::const_iterator i = GetChildren().begin();
       i != GetChildren().end(); ++i)
  {
    (*i)->render();
  }
}
