#include <GLFW/glfw3.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

#include "Renderer.h"

int main() {

    // Inicializar GLFW
    if (!glfwInit())
        return -1;

    // Crear ventana
    GLFWwindow* window =
        glfwCreateWindow(
            800,
            600,
            "Dark Prince - OpenGL",
            NULL,
            NULL
        );

    if (!window) {

        glfwTerminate();
        return -1;
    }

    // Activar contexto OpenGL
    glfwMakeContextCurrent(window);

    // Renderer principal
    Renderer renderer;

    // Inicializar renderer
    renderer.init(800, 600);

    // ==========================================
    // SCROLL DEL MOUSE
    // ==========================================

    // Permite acceder al renderer
    // desde el callback
    glfwSetWindowUserPointer(window, &renderer);

    // Callback del scroll
    glfwSetScrollCallback(
        window,
        Renderer::scrollCallback
    );

    // ==========================================
    // LOOP PRINCIPAL
    // ==========================================
    while (!glfwWindowShouldClose(window)) {

        // Inputs
        renderer.processInput(window);

        // Dibujar escena
        renderer.display();

        // Actualizar ventana
        glfwSwapBuffers(window);

        // Eventos
        glfwPollEvents();
    }

    // Cerrar GLFW
    glfwTerminate();

    return 0;
}