#include "Shader.h"
#include "Mesh.h"

/*
It's nice to have a robust program, that can handle things going wrong in them!
To enhance the robustness of your coursework, I've added some functionality not
really discussed in the tutorial notes. If one of your shader programs fails to
compile for some reason, it will revert to using a default vertex and fragment
program, that transforms the cube correctly, but makes it bright pink, to make
it obvious that something's gone wrong! You can test in your code whether a
shader has failed in such a way using the UsingDefaultShader function.

If you really want, you can disable this by commenting out the define below.
*/

#define BACKUP_SHADER

#ifdef BACKUP_SHADER
const string defaultVertex = "#version 150 core\n"
                             "uniform mat4 modelMatrix;"
                             "uniform mat4 viewMatrix; "
                             "uniform mat4 projMatrix; "
                             "in  vec3 position;"
                             "in  vec2 texCoord;"
                             "in  vec4 colour;  "
                             "out Vertex{		"
                             "	vec2 texCoord;	"
                             "	vec4 colour;	"
                             "} OUT;				"
                             "void main(void)	{"
                             "	gl_Position = (projMatrix * viewMatrix * "
                             "modelMatrix) * vec4(position, 1.0);"
                             "	OUT.texCoord = texCoord;"
                             "	OUT.colour	 = colour;"
                             "}";

const string defaultFragment = "#version 150 core\n"
                               "in Vertex{"
                               "	vec2 texCoord;"
                               "	vec4 colour;"
                               "} IN;"
                               "out vec4 fragColor;"
                               "void main(void)	{"
                               "	fragColor = vec4(1,0,1,1);"
                               "}";
#endif

/*
OpenGL shader programs can have many different combinations of
vertex/fragment/geometry/tcs/tes, so I've made a combined constructor that can
handle this. Just use "" as the parameter for any shader stage you aren't using,
as the code checks for non-empty strings. As you must always have a vertex and
fragment shader stage, these come first, while the others are defaulted to "".

Unlike most other OpenGL objects, you can't create multiple programs at once,
you just receive a program name from the glCreateProgram function - I'm not
sure why they did this!

I've done a trick both in here and in the Mesh class involving how enums are
created - by default a new enum will be 1 larger than the previous entry. This
means that if you start your first enum entry with a value of 0, the last entry
will be a value suitable for using as an array size to keep all of the previous
entries. I use this to create a compile-time array large enough to store all of
the possible shader objects we might need, using an easy-to-read variable name.
*/
Shader::Shader(string vFile, string fFile, string gFile, string tcsFile,
               string tesFile)
{
  linkSuccess = true;
  loadSuccess = true;

  usingBackupShader = false;

  program = glCreateProgram();
  objects[SHADER_VERTEX] = GenerateShader(vFile, GL_VERTEX_SHADER);
  objects[SHADER_FRAGMENT] = GenerateShader(fFile, GL_FRAGMENT_SHADER);
  objects[SHADER_GEOMETRY] = 0;
  objects[SHADER_TCS] = 0;
  objects[SHADER_TES] = 0;

  if (!gFile.empty())
  {
    objects[SHADER_GEOMETRY] = GenerateShader(gFile, GL_GEOMETRY_SHADER);
  }
  if (!tcsFile.empty())
  {
    objects[SHADER_TCS] = GenerateShader(tcsFile, GL_TESS_CONTROL_SHADER);
  }
  if (!tesFile.empty())
  {
    objects[SHADER_TES] = GenerateShader(tesFile, GL_TESS_EVALUATION_SHADER);
  }

  for (int i = 0; i < SHADER_MAX; ++i)
  {
    if (objects[i])
    {
      glAttachShader(program, objects[i]);
    }
  }

  SetDefaultAttributes();
  linkSuccess = LinkProgram();

#ifdef BACKUP_SHADER
  if (!linkSuccess || !loadSuccess)
  {
    LoadDefaultShader();
  }
#endif
}

/*
It's good practice to destruct all of your OpenGL objects. For your
projects it probably doesn't matter (all objects will be destroyed when
the parent OpenGL context is destroyed), but its conceivable that you
could have some system that deletes and constructs shaders at runtime
(such as a button to reload all your shaders - this can be a time saver!)

*/
Shader::~Shader(void)
{
  if (program)
  {
    for (int i = 0; i < SHADER_MAX; ++i)
    {
      if (objects[i])
      {
        glDetachShader(program, objects[i]);
        glDeleteShader(objects[i]);
      }
    }
    glDeleteProgram(program);
  }
}

/*
Basic text file loading. Should be pretty efficient as the text
buffer will only be made once, and never resized.
*/
bool Shader::LoadShaderFile(string from, string &into)
{
  ifstream file;

  file.open(from);
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
  cout << "Loaded shader text!" << endl
       << endl;
  return true;
}

/*
The shader files you create are just text - they must be compiled into
machine code compatible with your graphics card, just as with your C++ code.

All shader objects are of a specific 'type' (vertex/fragment/geometry etc),
so when you create a shader object using glCreateShader, you must set this.

One you have loaded a shader file, you can tell OpenGL about it using the
glShaderSource function - you can send multiple text files at once using this
function, so you could create your own #include system by parsing your text
files. Once you've sent the text to OpenGL, you can tell it to turn it into
a shader object using glCompileShader. If your driver fails to compile the
code, you can query information on why its failed using the 'info log', which
will return a string telling you about what warnings and errors it found.
*/
GLuint Shader::GenerateShader(string from, GLenum type)
{
  cout << "Compiling Shader " << from << endl;

  string load;
  if (!LoadShaderFile(from, load))
  {
    cout << "Compiling failed! File not found!" << endl;
    loadSuccess = false;
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
    loadSuccess = false;
    return false;
  }
  cout << "Compiling success!" << endl
       << endl;
  return shader;
}

/*
In order to create a finished working shader program, you must 'link' all of
your shader objects together - this makes sure the outputs of one stage connect
to the inputs of the next stage. In case this linking stage fails, it is
possible
to get an 'info log' from your OpenGL driver, which should (hopefully) inform
you
of why.
*/
bool Shader::LinkProgram()
{
  if (!loadSuccess)
  {
    cout << "Can't link program, one or more shader objects have failed!"
         << endl;
    return false;
  }
  glLinkProgram(program);

  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);

  if (status == GL_FALSE)
  {
    cout << "Linking failed! Error log as follows:" << endl;
    char error[2048];
    glGetProgramInfoLog(program, sizeof(error), NULL, error);
    cout << error << endl;
    return false;
  }
  return true;
}

/*
When a vertex buffer is bound to the pipeline, it is attached to a
specific generic 'attribute', numbered between 0 and whatever the max
your driver implementation can do (generally this is at least 15).

Your shader needs to know how to interpret these generic attributes, and it
can do this in one of two ways - either 'layout qualifiers' in the vertex
shader itself, or by using the glBindAttribLocation function. For basic vertex
data that is used across lots of shaders, I prefer the latter method, as it acts
as a generic interface that any shader will work with as long as it uses the
same
variable names, without having to really care about how the data is sent to it.

The glBindAttribLocation takes 3 parameters, a shader program, a generic
attribute
index, and a string variable name, which will be an 'in' value in the vertex
shader.

As you can see, I've matched up these generic attribute indices to the mesh
class vertex
buffers, so the connecting of vertex buffers to any shader loaded via my class
happens
'automagically'. It's perfectly safe to attempt to bind a non-existant input
variable,
so it's generally a good idea to just attempt to bind all of your commonly used
vertex
attributes

*/
void Shader::SetDefaultAttributes()
{
  glBindAttribLocation(program, VERTEX_BUFFER, "position");
  glBindAttribLocation(program, COLOUR_BUFFER, "colour");
  glBindAttribLocation(program, NORMAL_BUFFER, "normal");
  glBindAttribLocation(program, TANGENT_BUFFER, "tangent");
  glBindAttribLocation(program, TEXTURE_BUFFER, "texCoord");
}

/*
If your shader all goes wrong, this function will be called, to create the
emergency 'default' shader. It goes through all of the stages outlined in
the tutorial notes, but instead of reading from a file, it uses some const
strings I defined at the top
*/
void Shader::LoadDefaultShader()
{
  for (int i = 0; i < SHADER_MAX; ++i)
  {
    if (objects[i])
    {
      glDetachShader(program, objects[i]);
      glDeleteShader(objects[i]);
      objects[i] = 0;
    }
  }
  loadSuccess = true;
  linkSuccess = true;
  usingBackupShader = true;

  const char *vertchars = defaultVertex.c_str();
  const char *fragchars = defaultFragment.c_str();

  objects[SHADER_VERTEX] = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(objects[SHADER_VERTEX], 1, &vertchars, NULL);
  glCompileShader(objects[SHADER_VERTEX]);

  objects[SHADER_FRAGMENT] = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(objects[SHADER_FRAGMENT], 1, &fragchars, NULL);
  glCompileShader(objects[SHADER_FRAGMENT]);

  glAttachShader(program, objects[SHADER_VERTEX]);
  glAttachShader(program, objects[SHADER_FRAGMENT]);

  SetDefaultAttributes();
  linkSuccess = LinkProgram();

  cout << "Your shader program has failed! Reverting to default shader..."
       << endl;
}
