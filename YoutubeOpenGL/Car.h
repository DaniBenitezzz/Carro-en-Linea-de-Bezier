#ifndef CAR_H
#define CAR_H

class Car {

private:

    float rotation;

    float posX;
    float posY;
    float posZ;

public:

    Car();

    void rotate(float speed);

    void setRotation(float angle);

    void setPosition(float x, float y, float z);

    void draw();

    void drawCube(
        float width,
        float height,
        float depth
    );
};

#endif