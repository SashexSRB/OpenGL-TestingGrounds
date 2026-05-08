#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "renderer.h"

#define WIDTH 1200
#define HEIGHT 675

int main(int argc, char **argv) {
    if (glfwInit() != GLFW_TRUE) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "DOOT", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return 1;
    }

    rendererInit(WIDTH, HEIGHT);

    char title[128];
    float last = 0.f;
    while (!glfwWindowShouldClose(window)) {
        float now = glfwGetTime();
        float delta = now - last;
        last = now;

        glfwPollEvents();
        snprintf(title, 128, "DOOT | %.0f", 1.f / delta);
        glfwSetWindowTitle(window, title);

        rendererClear();

        rendererDrawPoint(
            (vec2_t){WIDTH / 2.f, HEIGHT / 2.f}, 5.f,
            (vec4_t){1.f, 1.f, 1.f, 1.f}
        );

        rendererDrawQuad(
            (vec2_t){100.f, 100.f},
            (vec2_t){40.f, 40.f},
            M_PI_4,
            (vec4_t){1.f, 1.f, 0.f, 1.f}
        );
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}