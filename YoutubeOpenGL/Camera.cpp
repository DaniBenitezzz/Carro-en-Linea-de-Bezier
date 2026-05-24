#include "Camera.h"

Camera::Camera()
    : x(0.0f),
    y(-2.0f),
    z(-20.0f),
    rotationX(20.0f),
    rotationY(0.0f) {
}

// ==========================================
// ROTACIÓN
// ==========================================

void Camera::rotate(
    float deltaX,
    float deltaY
) {

    rotationY += deltaX;

    rotationX += deltaY;

    if (rotationX > 89.0f)
        rotationX = 89.0f;

    if (rotationX < -89.0f)
        rotationX = -89.0f;
}

// ==========================================
// ZOOM
// ==========================================

void Camera::moveForward(float speed) {

    z += speed;
}

void Camera::moveBackward(float speed) {

    z -= speed;
}

// ==========================================
// GETTERS POSICIÓN
// ==========================================

float Camera::getX() const {

    return x;
}

float Camera::getY() const {

    return y;
}

float Camera::getZ() const {

    return z;
}

// ==========================================
// GETTERS ROTACIÓN
// ==========================================

float Camera::getRotationX() const {

    return rotationX;
}

float Camera::getRotationY() const {

    return rotationY;
}