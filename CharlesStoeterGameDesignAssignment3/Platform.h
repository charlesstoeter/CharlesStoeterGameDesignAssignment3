#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

#include <allegro5/allegro.h>

class Platform {
public:
    Platform(int x, int y, int width, int height);

    void draw() const;
    void damage();// Call when hit by asteroid
    bool isGameOver() const;

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

private:
    int x, y, width, height;
    int damageLevel;// 0 = full health, 5 = game over
};

#endif

