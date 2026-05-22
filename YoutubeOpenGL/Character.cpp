#include "Character.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

Character::Character()
    : rotation(0.0f),
    posX(0.0f),
    posY(0.0f),
    posZ(0.0f) {}

void Character::rotate(float speed) {
    rotation += speed;
}

void Character::setRotation(float angle) {
    rotation = angle;
}

void Character::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

void Character::drawCube(float width, float height, float depth) {

    float w = width / 2.0f;
    float h = height / 2.0f;
    float d = depth / 2.0f;

    glBegin(GL_QUADS);

    // Front
    glVertex3f(-w, -h, d);
    glVertex3f(w, -h, d);
    glVertex3f(w, h, d);
    glVertex3f(-w, h, d);

    // Back
    glVertex3f(-w, -h, -d);
    glVertex3f(-w, h, -d);
    glVertex3f(w, h, -d);
    glVertex3f(w, -h, -d);

    // Left
    glVertex3f(-w, -h, -d);
    glVertex3f(-w, -h, d);
    glVertex3f(-w, h, d);
    glVertex3f(-w, h, -d);

    // Right
    glVertex3f(w, -h, -d);
    glVertex3f(w, h, -d);
    glVertex3f(w, h, d);
    glVertex3f(w, -h, d);

    // Top
    glVertex3f(-w, h, -d);
    glVertex3f(-w, h, d);
    glVertex3f(w, h, d);
    glVertex3f(w, h, -d);

    // Bottom
    glVertex3f(-w, -h, -d);
    glVertex3f(w, -h, -d);
    glVertex3f(w, -h, d);
    glVertex3f(-w, -h, d);

    glEnd();
}

void Character::draw() {

    glPushMatrix();

    // Posición Bézier
    glTranslatef(posX, posY, posZ);

    // Rotación
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);

    // ==========================================
    // BODY ARMOR
    // ==========================================
    glColor3f(0.12f, 0.12f, 0.14f);
    drawCube(2.3f, 3.2f, 1.4f);

    // Chest plate
    glColor3f(0.25f, 0.25f, 0.28f);

    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.75f);
    drawCube(1.8f, 2.2f, 0.2f);
    glPopMatrix();

    // ==========================================
    // HELMET
    // ==========================================
    glColor3f(0.12f, 0.12f, 0.15f);

    glPushMatrix();
    glTranslatef(0.0f, 2.8f, 0.0f);
    drawCube(1.9f, 1.9f, 1.9f);
    glPopMatrix();

    // Helmet crest
    glColor3f(0.75f, 0.0f, 0.0f);

    glPushMatrix();
    glTranslatef(0.0f, 3.9f, 0.2f);
    drawCube(0.35f, 0.4f, 1.4f);
    glPopMatrix();

    // ==========================================
    // FACE
    // ==========================================

    // Skin
    glColor3f(0.92f, 0.77f, 0.63f);

    glPushMatrix();
    glTranslatef(0.0f, 2.8f, 0.96f);
    drawCube(1.4f, 1.1f, 0.02f);
    glPopMatrix();

    // LEFT EYE
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(-0.28f, 2.95f, 0.98f);
    drawCube(0.32f, 0.32f, 0.01f);
    glPopMatrix();

    glColor3f(0.4f, 0.7f, 1.0f);

    glPushMatrix();
    glTranslatef(-0.28f, 2.95f, 0.99f);
    drawCube(0.16f, 0.16f, 0.01f);
    glPopMatrix();

    // RIGHT EYE
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.28f, 2.95f, 0.98f);
    drawCube(0.32f, 0.32f, 0.01f);
    glPopMatrix();

    glColor3f(0.4f, 0.7f, 1.0f);

    glPushMatrix();
    glTranslatef(0.28f, 2.95f, 0.99f);
    drawCube(0.16f, 0.16f, 0.01f);
    glPopMatrix();

    // Nose
    glColor3f(0.85f, 0.50f, 0.55f);

    glPushMatrix();
    glTranslatef(0.0f, 2.60f, 0.99f);
    drawCube(0.25f, 0.35f, 0.01f);
    glPopMatrix();

    // ==========================================
    // LEGS
    // ==========================================
    glColor3f(0.1f, 0.1f, 0.12f);

    // Left leg
    glPushMatrix();

    glTranslatef(-0.6f, -2.5f, 0.0f);

    drawCube(0.7f, 1.6f, 0.7f);

    glColor3f(0.2f, 0.2f, 0.22f);

    glTranslatef(0.0f, -0.9f, 0.1f);

    drawCube(0.8f, 0.5f, 1.1f);

    glPopMatrix();

    // Right leg
    glColor3f(0.1f, 0.1f, 0.12f);

    glPushMatrix();

    glTranslatef(0.6f, -2.5f, 0.0f);

    drawCube(0.7f, 1.6f, 0.7f);

    glColor3f(0.2f, 0.2f, 0.22f);

    glTranslatef(0.0f, -0.9f, 0.1f);

    drawCube(0.8f, 0.5f, 1.1f);

    glPopMatrix();

    glPopMatrix();
}