/******************************************************************************
Class:Shader
Implements:
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Description:VERY simple class to encapsulate GLSL shader loading, linking,
and binding. Useful additions to this class would be overloaded functions to
replace the glUniformxx functions in external code, and possibly a map to store
uniform names and their resulting bindings.

-_-_-_-_-_-_-_,------,
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""

*/ /////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "GL/glew.h"

enum ShaderStage
{
  SHADER_VERTEX = 0,
  SHADER_FRAGMENT,
  SHADER_GEOMETRY,
  SHADER_TCS,
  SHADER_TES,
  SHADER_MAX
};

using namespace std;

class Shader
{
public:
  Shader(string vertex, string fragment, string geometry = "", string tcs = "",
         string tes = "");
  ~Shader();

  GLuint program() const
  {
    return m_program;
  }

  bool valid() const
  {
    return m_linkSuccess;
  }

private:
  bool loadFile(string filename, string &into);
  GLuint compile(string filename, GLenum type);
  bool link();
  void setDefaultAttributes();

  GLuint m_objects[SHADER_MAX];
  GLuint m_program;

  bool m_loadSuccess;
  bool m_linkSuccess;
};
