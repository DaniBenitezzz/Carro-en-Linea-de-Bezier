#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

#include "Renderer.h"

int main() {

    if (!glfwInit())
        return -1;

    GLFWwindow* window =
        glfwCreateWindow(
            800,
            600,
            "Bezier Car",
            NULL,
            NULL
        );

    if (!window) {

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);

    Renderer renderer;

    renderer.init(800, 600);

    float lastFrame =
        (float)glfwGetTime();

    while (!glfwWindowShouldClose(window)) {

        float currentFrame =
            (float)glfwGetTime();

        float deltaTime =
            currentFrame - lastFrame;

        lastFrame = currentFrame;

        // Mouse
        renderer.processMouse(window);

        // Teclado
        renderer.processInput(window);

        // Actualización
        renderer.update(deltaTime);

        // Render
        renderer.display();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}