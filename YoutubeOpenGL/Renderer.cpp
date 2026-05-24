#include "Renderer.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

#include <cmath>

// ==========================================
// VARIABLES INTERNAS DEL MOUSE
// ==========================================

namespace {

    double previousMouseX = 400.0;
    double previousMouseY = 300.0;

    bool firstClick = true;
}

// ==========================================
// CONSTRUCTOR
// ==========================================

Renderer::Renderer()
    : bezierT(0.0f) {
}

// ==========================================
// CONFIGURACIÓN INICIAL OPENGL
// ==========================================

void Renderer::init(int width, int height) {

    glEnable(GL_DEPTH_TEST);

    // Fondo oscuro
    glClearColor(
        0.05f,
        0.05f,
        0.1f,
        1.0f
    );

    float aspectRatio =
        static_cast<float>(width)
        / static_cast<float>(height);

    float nearValue = 1.0f;
    float farValue = 100.0f;

    float fov = 45.0f;

    float top =
        tan(fov * 3.14159265f / 360.0f)
        * nearValue;

    float right = top * aspectRatio;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glFrustum(
        -right,
        right,
        -top,
        top,
        nearValue,
        farValue
    );

    glMatrixMode(GL_MODELVIEW);
}

// ==========================================
// ECUACIÓN BÉZIER CÚBICA
// ==========================================

float Renderer::bezierPoint(
    float p0,
    float p1,
    float p2,
    float p3,
    float t
) {

    float inverse = 1.0f - t;

    float part1 =
        inverse * inverse * inverse * p0;

    float part2 =
        3.0f *
        inverse *
        inverse *
        t *
        p1;

    float part3 =
        3.0f *
        inverse *
        t *
        t *
        p2;

    float part4 =
        t * t * t * p3;

    return
        part1 +
        part2 +
        part3 +
        part4;
}

// ==========================================
// MOVIMIENTO DEL CARRO
// ==========================================

void Renderer::update(float deltaTime) {

    bezierT += deltaTime * 0.2f;

    if (bezierT >= 1.0f) {

        bezierT = 0.0f;
    }

    // Coordenadas actuales
    float currentX =
        bezierPoint(
            -10.0f,
            -5.0f,
            5.0f,
            10.0f,
            bezierT
        );

    float currentZ =
        bezierPoint(
            -10.0f,
            10.0f,
            -10.0f,
            10.0f,
            bezierT
        );

    car.setPosition(
        currentX,
        0.0f,
        currentZ
    );

    // Punto siguiente para calcular dirección
    float futureT = bezierT + 0.01f;

    if (futureT > 1.0f) {

        futureT = 1.0f;
    }

    float futureX =
        bezierPoint(
            -10.0f,
            -5.0f,
            5.0f,
            10.0f,
            futureT
        );

    float futureZ =
        bezierPoint(
            -10.0f,
            10.0f,
            -10.0f,
            10.0f,
            futureT
        );

    float directionX =
        futureX - currentX;

    float directionZ =
        futureZ - currentZ;

    float angle =
        atan2(directionX, directionZ)
        * 180.0f
        / 3.14159265f;

    car.setRotation(angle);
}

// ==========================================
// CONTROL DEL MOUSE
// ==========================================

void Renderer::processMouse(GLFWwindow* window) {

    bool pressed =
        glfwGetMouseButton(
            window,
            GLFW_MOUSE_BUTTON_LEFT
        ) == GLFW_PRESS;

    if (!pressed) {

        firstClick = true;

        return;
    }

    double currentMouseX;
    double currentMouseY;

    glfwGetCursorPos(
        window,
        &currentMouseX,
        &currentMouseY
    );

    if (firstClick) {

        previousMouseX = currentMouseX;
        previousMouseY = currentMouseY;

        firstClick = false;
    }

    float sensitivity = 0.1f;

    float offsetX =
        static_cast<float>(
            currentMouseX - previousMouseX
            ) * sensitivity;

    float offsetY =
        static_cast<float>(
            currentMouseY - previousMouseY
            ) * sensitivity;

    previousMouseX = currentMouseX;
    previousMouseY = currentMouseY;

    camera.rotate(
        offsetX,
        offsetY
    );
}

// ==========================================
// TECLADO
// ==========================================

void Renderer::processInput(GLFWwindow* window) {

    const float zoomSpeed = 0.05f;

    bool forward =
        glfwGetKey(window, GLFW_KEY_W)
        == GLFW_PRESS;

    bool backward =
        glfwGetKey(window, GLFW_KEY_S)
        == GLFW_PRESS;

    if (forward) {

        camera.moveForward(zoomSpeed);
    }

    if (backward) {

        camera.moveBackward(zoomSpeed);
    }
}

// ==========================================
// DIBUJAR CURVA
// ==========================================

void Renderer::drawBezierCurve() {

    // Línea cyan
    glColor3f(
        0.0f,
        1.0f,
        1.0f
    );

    glBegin(GL_LINE_STRIP);

    for (float t = 0.0f;
        t <= 1.0f;
        t += 0.01f) {

        float x =
            bezierPoint(
                -10.0f,
                -5.0f,
                5.0f,
                10.0f,
                t
            );

        float z =
            bezierPoint(
                -10.0f,
                10.0f,
                -10.0f,
                10.0f,
                t
            );

        glVertex3f(
            x,
            0.0f,
            z
        );
    }

    glEnd();
}

// ==========================================
// RENDER PRINCIPAL
// ==========================================

void Renderer::display() {

    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );

    glLoadIdentity();

    // Rotación cámara
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

    // Posición cámara
    glTranslatef(
        camera.getX(),
        camera.getY(),
        camera.getZ()
    );

    drawBezierCurve();

    car.draw();
}