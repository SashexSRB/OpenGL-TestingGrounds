#pragma once

#include <GL/glew.h>
#include <stddef.h>

GLuint compileShader(GLenum type, const char* src);
GLuint linkProgram(size_t numShaders, ...);