#ifndef RENDERER_H
#define RENDERER_H

// GLFW
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// Clases del proyecto
#include "Camera.h"
#include "Character.h"

class Renderer {

private:

    // Cámara principal
    Camera camera;

    // Personaje
    Character character;

public:

    // Constructor
    Renderer();

    // Inicializa OpenGL
    void init(int width, int height);

    // Dibuja toda la escena
    void display();

    // Detecta teclado y mouse
    void processInput(GLFWwindow* window);

    // Scroll del mouse
    static void scrollCallback(GLFWwindow* window,
        double xoffset,
        double yoffset);
};

#endif