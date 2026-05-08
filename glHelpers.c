#include "glHelpers.h"

#include <GL/glew.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

GLuint compileShader(GLenum type, const char* src) {
    GLuint shader= glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        char infolog[512];
        glGetShaderInfoLog(shader, sizeof(infolog), NULL, infolog);
        fprintf(stderr, "Failed to compile shader!\nInfo Log:\n%s\n", infolog);
    }

    return shader;
}
GLuint linkProgram(size_t numShaders, ...) {
    GLuint program = glCreateProgram();

    va_list va;
    va_start(va, numShaders);

    for (size_t i = 0; i < numShaders; i++) {
        glAttachShader(program, va_arg(va, GLuint));
    }

    va_end(va);

    glLinkProgram(program);
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        char infolog[512];
        glGetProgramInfoLog(program, sizeof(infolog), NULL, infolog);
        fprintf(stderr, "Failed to link shader program!\nInfo Log:\n%s\n", infolog);
    }

    return program;
}