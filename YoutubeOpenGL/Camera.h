#ifndef CAMERA_H
#define CAMERA_H

class Camera {

private:

    // Posición de la cámara en el mundo 3D
    float x, y, z;

    // Rotación vertical y horizontal
    float rotationX;
    float rotationY;

public:

    // Constructor
    Camera();

    // Movimiento adelante y atrás
    void moveForward(float speed);
    void moveBackward(float speed);

    // Movimiento lateral
    void moveLeft(float speed);
    void moveRight(float speed);

    // Movimiento vertical
    void moveUp(float speed);
    void moveDown(float speed);

    // Rotación con mouse
    void rotate(float deltaX, float deltaY);

    // Zoom con scroll
    void zoom(float amount);

    // Getters de posición
    float getX() const;
    float getY() const;
    float getZ() const;

    // Getters de rotación
    float getRotationX() const;
    float getRotationY() const;
};

#endif