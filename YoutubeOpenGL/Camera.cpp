#include "Camera.h"

// ==========================================
// CONSTRUCTOR
// ==========================================
// Inicializa la cámara en una posición inicial
Camera::Camera()
    : x(0.0f),
    y(2.0f),
    z(-12.0f),
    rotationY(0.0f),
    rotationX(0.0f) {}

// ==========================================
// MOVIMIENTO HACIA ADELANTE
// ==========================================
void Camera::moveForward(float speed) {
    z += speed;
}

// ==========================================
// MOVIMIENTO HACIA ATRÁS
// ==========================================
void Camera::moveBackward(float speed) {
    z -= speed;
}

// ==========================================
// MOVIMIENTO IZQUIERDA
// ==========================================
void Camera::moveLeft(float speed) {
    x += speed;
}

// ==========================================
// MOVIMIENTO DERECHA
// ==========================================
void Camera::moveRight(float speed) {
    x -= speed;
}

// ==========================================
// MOVIMIENTO HACIA ARRIBA
// ==========================================
void Camera::moveUp(float speed) {
    y += speed;
}

// ==========================================
// MOVIMIENTO HACIA ABAJO
// ==========================================
void Camera::moveDown(float speed) {
    y -= speed;
}

// ==========================================
// ROTACIÓN DE CÁMARA
// ==========================================
// deltaX = movimiento horizontal del mouse
// deltaY = movimiento vertical del mouse
void Camera::rotate(float deltaX, float deltaY) {

    rotationY += deltaX;
    rotationX += deltaY;

    // Limitar rotación vertical
    // para evitar que la cámara se invierta
    if (rotationX > 89.0f)
        rotationX = 89.0f;

    if (rotationX < -89.0f)
        rotationX = -89.0f;
}

// ==========================================
// ZOOM CON SCROLL
// ==========================================
// Acerca o aleja la cámara
void Camera::zoom(float amount) {
    z += amount;
}

// ==========================================
// GETTERS
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

float Camera::getRotationX() const {
    return rotationX;
}

float Camera::getRotationY() const {
    return rotationY;
}