#include "Renderer.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

#include <cmath>

// ==========================================
// VARIABLES DEL MOUSE
// ==========================================

// Última posición del mouse
static double lastMouseX = 400;
static double lastMouseY = 300;

// Detecta primer movimiento
static bool firstMouse = true;

// ==========================================
// VARIABLE DE LA CURVA BÉZIER
// ==========================================

// Parámetro de recorrido
float bezierT = 0.0f;

// Tiempo anterior
float lastTime = 0.0f;

// ==========================================
// CONSTRUCTOR
// ==========================================
Renderer::Renderer() {}

// ==========================================
// CALLBACK DEL SCROLL
// ==========================================
// Se ejecuta automáticamente
// cuando el usuario mueve el scroll
void Renderer::scrollCallback(GLFWwindow* window,
    double xoffset,
    double yoffset) {

    Renderer* renderer =
        static_cast<Renderer*>(glfwGetWindowUserPointer(window));

    if (renderer) {

        // Zoom cámara
        renderer->camera.zoom((float)yoffset * 0.7f);
    }
}

// ==========================================
// DIBUJAR CURVA BÉZIER
// ==========================================
// Dibuja la trayectoria del personaje
void drawBezierCurve() {

    glColor3f(1.0f, 1.0f, 0.0f);

    glBegin(GL_LINE_STRIP);

    // Recorre la curva
    for (float t = 0; t <= 1.0f; t += 0.01f) {

        // Fórmula Bézier cúbica

        float x =
            pow(1 - t, 3) * -8 +
            3 * pow(1 - t, 2) * t * -4 +
            3 * (1 - t) * pow(t, 2) * 4 +
            pow(t, 3) * 8;

        float y = 0.0f;

        float z =
            pow(1 - t, 3) * -5 +
            3 * pow(1 - t, 2) * t * 8 +
            3 * (1 - t) * pow(t, 2) * -8 +
            pow(t, 3) * 5;

        glVertex3f(x, y, z);
    }

    glEnd();
}

// ==========================================
// INICIALIZACIÓN DE OPENGL
// ==========================================
void Renderer::init(int width, int height) {

    // Activar profundidad
    glEnable(GL_DEPTH_TEST);

    // Color del fondo
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);

    // Relación de aspecto
    float aspect =
        (float)width / (float)height;

    // Parámetros de cámara
    float nearPlane = 1.0f;
    float farPlane = 100.0f;
    float fov = 45.0f;

    // Cálculo del frustum
    float top =
        tan(fov * 3.14159265f / 360.0f)
        * nearPlane;

    float bottom = -top;

    float right = top * aspect;
    float left = -right;

    // Matriz de proyección
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glFrustum(
        left,
        right,
        bottom,
        top,
        nearPlane,
        farPlane
    );

    // Volver a modelview
    glMatrixMode(GL_MODELVIEW);
}

// ==========================================
// DIBUJAR ESCENA
// ==========================================
void Renderer::display() {

    // Limpiar pantalla
    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    // ==========================================
    // ROTACIÓN CÁMARA
    // ==========================================
    glRotatef(
        camera.getRotationX(),
        1.0f,
        0.0f,
        0.0f
    );

    glRotatef(
        camera.getRotationY(),
        0.0f,
        1.0f,
        0.0f
    );

    // ==========================================
    // MOVIMIENTO CÁMARA
    // ==========================================
    glTranslatef(
        camera.getX(),
        -camera.getY(),
        camera.getZ()
    );

    // ==========================================
    // DIBUJAR CURVA
    // ==========================================
    drawBezierCurve();

    // ==========================================
    // DELTA TIME
    // ==========================================
    float currentTime =
        (float)glfwGetTime();

    float deltaTime =
        currentTime - lastTime;

    lastTime = currentTime;

    // ==========================================
    // MOVIMIENTO BÉZIER
    // ==========================================
    float t = bezierT;

    // Fórmula posición X
    float x =
        pow(1 - t, 3) * -8 +
        3 * pow(1 - t, 2) * t * -4 +
        3 * (1 - t) * pow(t, 2) * 4 +
        pow(t, 3) * 8;

    // Fórmula posición Z
    float z =
        pow(1 - t, 3) * -5 +
        3 * pow(1 - t, 2) * t * 8 +
        3 * (1 - t) * pow(t, 2) * -8 +
        pow(t, 3) * 5;

    // ==========================================
    // DERIVADA PARA ROTACIÓN
    // ==========================================
    float dx =
        -3 * pow(1 - t, 2) * -8 +
        3 * (pow(1 - t, 2) -
            2 * t * (1 - t)) * -4 +
        3 * ((2 * t * (1 - t)) -
            pow(t, 2)) * 4 +
        3 * pow(t, 2) * 8;

    float dz =
        -3 * pow(1 - t, 2) * -5 +
        3 * (pow(1 - t, 2) -
            2 * t * (1 - t)) * 8 +
        3 * ((2 * t * (1 - t)) -
            pow(t, 2)) * -8 +
        3 * pow(t, 2) * 5;

    // Convertir dirección a ángulo
    float angle =
        atan2(dx, dz)
        * 180.0f
        / 3.14159265f;

    // Aplicar posición
    character.setPosition(
        x,
        0.0f,
        z
    );

    // Aplicar rotación
    character.setRotation(angle);

    // ==========================================
    // AVANZAR EN LA CURVA
    // ==========================================
    bezierT += deltaTime * 0.03f;

    if (bezierT > 1.0f)
        bezierT = 0.0f;

    // Dibujar personaje
    character.draw();
}

// ==========================================
// INPUTS
// ==========================================
void Renderer::processInput(GLFWwindow* window) {

    // Velocidades
    float zoomSpeed = 0.01f;
    float sideSpeed = 0.01f;
    float verticalSpeed = 0.01f;

    float mouseSensitivity = 0.1f;

    // ==========================================
    // MOVIMIENTO CÁMARA
    // ==========================================

    // Izquierda
    if (glfwGetKey(window,
        GLFW_KEY_D) == GLFW_PRESS)

        camera.moveLeft(sideSpeed);

    // Derecha
    if (glfwGetKey(window,
        GLFW_KEY_A) == GLFW_PRESS)

        camera.moveRight(sideSpeed);

    // Arriba
    if (glfwGetKey(window,
        GLFW_KEY_W) == GLFW_PRESS)

        camera.moveUp(verticalSpeed);

    // Abajo
    if (glfwGetKey(window,
        GLFW_KEY_S) == GLFW_PRESS)

        camera.moveDown(verticalSpeed);

    // ==========================================
    // ROTACIÓN CON MOUSE
    // ==========================================
    if (glfwGetMouseButton(window,
        GLFW_MOUSE_BUTTON_LEFT)
        == GLFW_PRESS) {

        double xpos, ypos;

        glfwGetCursorPos(
            window,
            &xpos,
            &ypos
        );

        if (firstMouse) {

            lastMouseX = xpos;
            lastMouseY = ypos;

            firstMouse = false;
        }

        float deltaX =
            (float)(xpos - lastMouseX)
            * mouseSensitivity;

        float deltaY =
            (float)(ypos - lastMouseY)
            * mouseSensitivity;

        lastMouseX = xpos;
        lastMouseY = ypos;

        camera.rotate(deltaX, deltaY);
    }
    else {
        firstMouse = true;
    }
}