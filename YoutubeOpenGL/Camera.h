#ifndef CAMERA_H
#define CAMERA_H

class Camera {

private:

    float x;
    float y;
    float z;

    float rotationX;
    float rotationY;

public:

    Camera();

    // Rotación
    void rotate(
        float deltaX,
        float deltaY
    );

    // Zoom
    void moveForward(float speed);

    void moveBackward(float speed);

    // Posición
    float getX() const;

    float getY() const;

    float getZ() const;

    // Rotación
    float getRotationX() const;

    float getRotationY() const;
};

#endif