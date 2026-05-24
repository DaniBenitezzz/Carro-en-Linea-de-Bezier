#ifndef RENDERER_H
#define RENDERER_H

#include "Camera.h"
#include "Car.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Renderer {

private:

    Camera camera;

    Car car;

    float bezierT;

    // Curva Bézier
    float bezierPoint(
        float p0,
        float p1,
        float p2,
        float p3,
        float t
    );

    // Dibujar línea
    void drawBezierCurve();

public:

    Renderer();

    void init(
        int width,
        int height
    );

    void update(float deltaTime);

    void display();

    void processMouse(GLFWwindow* window);

    void processInput(GLFWwindow* window);
};

#endif