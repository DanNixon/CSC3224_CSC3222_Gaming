/** @file */

#include "Shader.h"
#include "Mesh.h"

/**
 * @brief Creates a new shader collection.
 * @param vFile Filename for the vertex shader
 * @param fFile Filename for the fragment shader
 * @param gFile Filename for the geometry shader (optional)
 * @param tcsFile Filename for the tessellation control shader (optional)
 * @param tesFile Filename for the tessellation evaluation shader (optional)
 */
Shader::Shader(string vFile, string fFile, string gFile, string tcsFile,
               string tesFile)
    : m_linkSuccess(true)
    , m_loadSuccess(true)
{
  m_program = glCreateProgram();

  m_objects[SHADER_VERTEX] = compile(vFile, GL_VERTEX_SHADER);
  m_objects[SHADER_FRAGMENT] = compile(fFile, GL_FRAGMENT_SHADER);
  m_objects[SHADER_GEOMETRY] = 0;
  m_objects[SHADER_TCS] = 0;
  m_objects[SHADER_TES] = 0;

  if (!gFile.empty())
    m_objects[SHADER_GEOMETRY] = compile(gFile, GL_GEOMETRY_SHADER);

  if (!tcsFile.empty())
    m_objects[SHADER_TCS] = compile(tcsFile, GL_TESS_CONTROL_SHADER);

  if (!tesFile.empty())
    m_objects[SHADER_TES] = compile(tesFile, GL_TESS_EVALUATION_SHADER);

  for (int i = 0; i < SHADER_MAX; ++i)
  {
    if (m_objects[i])
    {
      glAttachShader(m_program, m_objects[i]);
    }
  }

  setDefaultAttributes();
  m_linkSuccess = link();
}

/**
 * @brief Deletes the programs associated with the loaded shaders.
 */
Shader::~Shader(void)
{
  if (m_program)
  {
    for (int i = 0; i < SHADER_MAX; ++i)
    {
      if (m_objects[i])
      {
        glDetachShader(m_program, m_objects[i]);
        glDeleteShader(m_objects[i]);
      }
    }
    glDeleteProgram(m_program);
  }
}

/**
 * @brief Loads the contents of a file into a string.
 * @param filename Name of file to load
 * @param into [out] String to store contents in
 * @return True on success, false if file is not found
 */
bool Shader::loadFile(string filename, string &into)
{
  ifstream file;

  file.open(filename);
  if (!file)
  {
    cout << "File does not exist!" << endl;
    return false;
  }

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
 * @param filename Filename of GLSL source file
 * @param type Shader type
 * @return Shader ID
 */
GLuint Shader::compile(string filename, GLenum type)
{
  string load;
  if (!loadFile(filename, load))
  {
    cout << "Compiling failed! File not found!" << endl;
    m_loadSuccess = false;
    return 0;
  }

  GLuint shader = glCreateShader(type);

  const char *chars = load.c_str();
  glShaderSource(shader, 1, &chars, NULL);
  glCompileShader(shader);

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

  if (status == GL_FALSE)
  {
    cout << "Compiling failed! Error log as follows:" << endl;
    char error[2048];
    glGetInfoLogARB(shader, sizeof(error), NULL, error);
    cout << error << endl;
    m_loadSuccess = false;
    return false;
  }

  return shader;
}

/**
 * @brief Links the loaded shaders.
 * @return True on success
 */
bool Shader::link()
{
  if (!m_loadSuccess)
  {
    cout << "Can't link m_program, one or more shader m_objects have failed!"
         << endl;
    return false;
  }
  glLinkProgram(m_program);

  GLint status;
  glGetProgramiv(m_program, GL_LINK_STATUS, &status);

  if (status == GL_FALSE)
  {
    cout << "Linking failed! Error log as follows:" << endl;
    char error[2048];
    glGetProgramInfoLog(m_program, sizeof(error), NULL, error);
    cout << error << endl;
    return false;
  }

  return true;
}

void Shader::setDefaultAttributes()
{
  glBindAttribLocation(m_program, VERTEX_BUFFER, "position");
  glBindAttribLocation(m_program, COLOUR_BUFFER, "colour");
  glBindAttribLocation(m_program, NORMAL_BUFFER, "normal");
  glBindAttribLocation(m_program, TANGENT_BUFFER, "tangent");
  glBindAttribLocation(m_program, TEXTURE_BUFFER, "texCoord");
}
