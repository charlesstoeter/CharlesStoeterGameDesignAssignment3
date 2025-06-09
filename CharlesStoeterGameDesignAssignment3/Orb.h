#pragma once
#ifndef ORB_H
#define ORB_H

#include <allegro5/allegro.h>

class Orb {
public:
    Orb();  // Constructor
    void fire(int startX, int startY, float angle, ALLEGRO_BITMAP* img);
    void update();
    void draw();
    void deactivate();
    bool isLive() const;
    int getX() const;
    int getY() const;


private:
    int x, y;
    float radianAngle;
    int speed;
    bool live;
    ALLEGRO_BITMAP* image;
};

#endif