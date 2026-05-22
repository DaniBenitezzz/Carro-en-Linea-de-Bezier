#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
private:
    float rotation;

    float posX;
    float posY;
    float posZ;

public:
    Character();

    void rotate(float speed);
    void setRotation(float angle);

    void setPosition(float x, float y, float z);

    void drawCube(float width, float height, float depth);

    void draw();
};

#endif