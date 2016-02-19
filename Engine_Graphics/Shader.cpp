/**
 * @file
 * @author Dan Nixon
 */

#include "Shader.h"
#include "Mesh.h"

/**
 * @brief Creates a new shader collection.
 */
Shader::Shader(std::string filename, GLuint stage)
    : m_valid(false)
    , m_stage(stage)
{
  m_valid = compile(filename);
}

/**
 * @brief Deletes the programs associated with the shader.
 */
Shader::~Shader(void)
{
  glDeleteShader(m_shaderObject);
}

/**
 * @brief Loads the contents of a file into a string.
 * @param filename Name of file to load
 * @param into [out] String to store contents in
 * @return True on success, false if file is not found
 */
bool Shader::loadFile(std::string filename, std::string &into)
{
  ifstream file;

  file.open(filename);
  if (!file)
    return false;

  file.seekg(0, std::ios::end);
  into.resize(1 + (unsigned int)file.tellg());
  file.seekg(0, std::ios::beg);
  file.read(&into[0], into.size());

  into[into.size() - 1] = '\n';

  file.close();
  return true;
}

/**
 * @brief Compiles a shader.
 */
bool Shader::compile(std::string filename)
{
  std::string load;
  if (!loadFile(filename, load))
    return false;

  m_shaderObject = glCreateShader(m_stage);

  const char *chars = load.c_str();
  glShaderSource(m_shaderObject, 1, &chars, NULL);
  glCompileShader(m_shaderObject);

  GLint status;
  glGetShaderiv(m_shaderObject, GL_COMPILE_STATUS, &status);
  return (status != GL_FALSE);
}
