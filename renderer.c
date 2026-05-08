#include "renderer.h"

#include <math.h>

#include "matrix.h"
#include "glHelpers.h"
#include <GL/glew.h>

static void initQuad();
static void initShader();
static void initProjection();

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
static GLuint modelLocation;
static GLuint colorLocation;

void rendererInit(int w, int h) {
    width = w;
    height = h;

    glClearColor(.2f, .2f, .2f, 1.f);

    initQuad();
    initShader();
    initProjection();
}

void rendererClear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void rendererDrawPoint(vec2_t point, float size, vec4_t color) {
    mat4_t translation = mat4Translate((vec3_t){point.x, point.y, 0.f});
    mat4_t scale = mat4Scale((vec3_t){size, size, 1.f});
    mat4_t model = mat4Multiply(scale, translation);

    glUniform4fv(colorLocation, 1, color.v);
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, model.v);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

void rendererDrawQuad(vec2_t center, vec2_t size, float angle, vec4_t color) {
    mat4_t translation = mat4Translate((vec3_t){center.x, center.y, 0.f});
    mat4_t scale = mat4Scale((vec3_t){size.x, size.y, 1.f});
    mat4_t rotation = mat4Rotate((vec3_t){0.f, 0.f, 1.f}, angle);
    mat4_t model = mat4Multiply(mat4Multiply(scale, rotation), translation);

    glUniform4fv(colorLocation, 1, color.v);
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, model.v);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

void rendererDrawLine(vec2_t p0, vec2_t p1, float width, vec4_t color) {
    float x = p1.x - p0.x;
    float y = p0.y - p1.y;

    float r = sqrtf(x * x + y * y);
    float theta = atan2f(y, x);


    mat4_t translation = mat4Translate((vec3_t){(p0.x + p1.x) / 2.f, (p0.y + p1.y) / 2.f, 0.f});
    mat4_t scale = mat4Scale((vec3_t){r, width, 1.f});
    mat4_t rotation = mat4Rotate((vec3_t){0.f, 0.f, 1.f}, theta);
    mat4_t model = mat4Multiply(mat4Multiply(scale, rotation), translation);

    glUniform4fv(colorLocation, 1, color.v);
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, model.v);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
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
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2* sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void initShader() {
    GLuint vertex = compileShader(GL_VERTEX_SHADER, vertSrc);
    GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragSrc);

    program = linkProgram(2, vertex, fragment);

    glUseProgram(program);

    modelLocation = glGetUniformLocation(program, "model");
    colorLocation = glGetUniformLocation(program, "color");
}

static void initProjection() {
    mat4_t projection = mat4Ortho(0.f, width, height, 0.f, -1.f, 1.f);
    GLuint projectionLocation = glGetUniformLocation(program, "projection");

    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projection.v);
}
















