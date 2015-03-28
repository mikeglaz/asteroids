#include <cstdio>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

namespace mgl {
  GLuint read_shader(const char*, GLenum);
  GLuint load_shaders(const char*, const char*);
}