#pragma once
#ifndef ASTEROID_H
#define ASTEROID_H

#include <allegro5/allegro.h>

class Asteroid {
public:
    Asteroid();
    ~Asteroid();

    void start(int screenW);
    void update();
    void draw();
    void collideWithGround();  // For iceberg collision if needed

    void loadImage(const char* filename);

    void setLive(bool l);
    bool isLive() const;

    int getX() const;
    int getY() const;
    int getBoundX() const;
    int getBoundY() const;


    ALLEGRO_BITMAP* getBitmap() const;

private:
    int x, y;
    int speed;
    int boundX, boundY;
    bool live;
    ALLEGRO_BITMAP* image;
};

#endif
