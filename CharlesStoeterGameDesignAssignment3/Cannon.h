#pragma once
#ifndef CANNON_H
#define CANNON_H

#include <allegro5/allegro.h>

class Cannon {
public:
    Cannon(int x, int y);
    ~Cannon();

    void loadImage(const char* filename);
    void rotateLeft();
    void rotateRight();
    void draw();
    float getAngle() const;
    int getX() const;
    int getY() const;

private:
    ALLEGRO_BITMAP* image;
    int x, y;
    float angle;
};

#endif
