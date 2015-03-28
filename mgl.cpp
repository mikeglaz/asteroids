#include "mgl.h"

using namespace std;

namespace mgl{
	GLuint read_shader(const char * filename, GLenum shader_type)
  {
    const char* const_source;
    GLchar* source = nullptr;
    int size = 0;
    GLuint shader;
    string shader_type_string;

    if(shader_type == GL_VERTEX_SHADER)
      shader_type_string = "vertex shader";
    else if(shader_type == GL_FRAGMENT_SHADER)
      shader_type_string = "fragment shader";

    GLint success;
    GLchar infoLog[512];

    FILE* infile = fopen( filename, "rb" );

    fseek( infile, 0, SEEK_END );
    int len = ftell( infile );
    fseek( infile, 0, SEEK_SET );

    source = new GLchar[len+1];

    fread( source, 1, len, infile );
    fclose( infile );

    source[len] = 0;

    const_source = const_cast<const GLchar*>(source);    
    shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &const_source, 0);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);

        cout << "Shader Compilation Failed: " << shader_type_string << endl << infoLog << endl;
    }

    delete [] source;

    return shader;
  }

GLuint load_shaders(const char* vertex_file, const char* frag_file)
{
  GLuint program = glCreateProgram();

  GLuint vertex_shader = read_shader(vertex_file, GL_VERTEX_SHADER);
  GLuint frag_shader = read_shader(frag_file, GL_FRAGMENT_SHADER);

  glAttachShader(program, vertex_shader);
  glAttachShader(program, frag_shader);
        
  glLinkProgram(program);

  GLint linked;
  glGetProgramiv(program, GL_LINK_STATUS, &linked);
  
  if (!linked)
  {
    GLsizei len;
    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

    GLchar* log = new GLchar[len+1];
    glGetProgramInfoLog(program, len, &len, log);
    
    std::cerr << "Shader linking failed: " << log << std::endl;
    delete [] log;
  }
    
  glDeleteShader(vertex_shader);
  glDeleteShader(frag_shader);

  return program;
}

}
