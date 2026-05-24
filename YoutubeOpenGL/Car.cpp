#include "Car.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

Car::Car()
    : rotation(0.0f),
    posX(0.0f),
    posY(0.0f),
    posZ(0.0f) {
}

// ==========================================
// ROTACIÓN
// ==========================================

void Car::rotate(float speed) {
    rotation += speed;
}

void Car::setRotation(float angle) {
    rotation = angle;
}

// ==========================================
// POSICIÓN
// ==========================================

void Car::setPosition(float x, float y, float z) {

    posX = x;

    posY = y;

    posZ = z;
}

// ==========================================
// DIBUJAR CUBO
// ==========================================

void Car::drawCube(
    float width,
    float height,
    float depth
) {

    float w = width / 2.0f;
    float h = height / 2.0f;
    float d = depth / 2.0f;

    glBegin(GL_QUADS);

    // FRONT
    glVertex3f(-w, -h, d);
    glVertex3f(w, -h, d);
    glVertex3f(w, h, d);
    glVertex3f(-w, h, d);

    // BACK
    glVertex3f(-w, -h, -d);
    glVertex3f(-w, h, -d);
    glVertex3f(w, h, -d);
    glVertex3f(w, -h, -d);

    // LEFT
    glVertex3f(-w, -h, -d);
    glVertex3f(-w, -h, d);
    glVertex3f(-w, h, d);
    glVertex3f(-w, h, -d);

    // RIGHT
    glVertex3f(w, -h, -d);
    glVertex3f(w, h, -d);
    glVertex3f(w, h, d);
    glVertex3f(w, -h, d);

    // TOP
    glVertex3f(-w, h, -d);
    glVertex3f(-w, h, d);
    glVertex3f(w, h, d);
    glVertex3f(w, h, -d);

    // BOTTOM
    glVertex3f(-w, -h, -d);
    glVertex3f(w, -h, -d);
    glVertex3f(w, -h, d);
    glVertex3f(-w, -h, d);

    glEnd();
}

// ==========================================
// DIBUJAR CARRO
// ==========================================

void Car::draw() {

    glPushMatrix();

    // Posición del carro
    glTranslatef(posX, posY, posZ);

    // Rotación del carro
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);

    // ==========================================
    // CARROCERÍA
    // ==========================================

    glColor3f(0.8f, 0.0f, 0.0f);

    glPushMatrix();

    drawCube(4.0f, 1.0f, 2.0f);

    glPopMatrix();

    // ==========================================
    // TECHO
    // ==========================================

    glColor3f(0.9f, 0.0f, 0.0f);

    glPushMatrix();

    glTranslatef(0.0f, 0.8f, 0.0f);

    drawCube(2.0f, 0.8f, 1.8f);

    glPopMatrix();

    // ==========================================
    // RUEDAS
    // ==========================================

    glColor3f(0.1f, 0.1f, 0.1f);

    // Delantera izquierda
    glPushMatrix();

    glTranslatef(-1.5f, -0.8f, 1.1f);

    drawCube(0.6f, 0.6f, 0.4f);

    glPopMatrix();

    // Delantera derecha
    glPushMatrix();

    glTranslatef(1.5f, -0.8f, 1.1f);

    drawCube(0.6f, 0.6f, 0.4f);

    glPopMatrix();

    // Trasera izquierda
    glPushMatrix();

    glTranslatef(-1.5f, -0.8f, -1.1f);

    drawCube(0.6f, 0.6f, 0.4f);

    glPopMatrix();

    // Trasera derecha
    glPushMatrix();

    glTranslatef(1.5f, -0.8f, -1.1f);

    drawCube(0.6f, 0.6f, 0.4f);

    glPopMatrix();

    // ==========================================
    // VENTANAS
    // ==========================================

    glColor3f(0.4f, 0.7f, 1.0f);

    glPushMatrix();

    glTranslatef(0.0f, 0.9f, 0.0f);

    drawCube(1.6f, 0.5f, 1.7f);

    glPopMatrix();

    glPopMatrix();
}