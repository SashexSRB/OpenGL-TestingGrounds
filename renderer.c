#include "renderer.h"
#include "glHelpers.h"
#include <GL/glew.h>

static void initShader();
static void initQuad();

const char *vertSrc =
    "#version 330 core\n"
    "layout (location = 0) in vec2 pos;\n"
    "uniform mat4 model;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "    gl_Position = projection * model * vec4(pos, 0.0, 1.0);\n"
    "}\n";

const char *fragSrc =
    "#version 330 core\n"
    "out vec4 fragColor;\n"
    "uniform vec4 color;\n"
    "void main() {\n"
    "    fragColor = color;\n"
    "}\n";

static float width, height;
static GLuint program;

void rendererInit(int w, int h) {
    width = w;
    height = h;

    glClearColor(.2f, .2f, .2f, 1.f);
}

void rendererClear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

static void initShader() {
    GLuint vertex = compileShader(GL_VERTEX_SHADER, vertSrc);
    GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragSrc);

    program = linkProgram(2, vertex, fragment);
}

static void initQuad() {
    float vertices[] = {
        .5f, .5f,   // top-right
        .5f, -.5f,  // bottom-right
        -.5f, -.5f, // bottom-left
        -.5f, .5f,  // bottom-right
    };

    uint32_t indices[] = {
        0, 1, 3,    // 1st triangle
        1, 2, 3,    // 2nd triangle
    };

    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2* sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}