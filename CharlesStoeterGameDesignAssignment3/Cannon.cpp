#include "Cannon.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <cmath>
#include <cstdio>

#define PI 3.14159265

Cannon::Cannon(int xPos, int yPos) {
    x = xPos;
    y = yPos;
    angle = 90.0f;
    image = nullptr;
}

Cannon::~Cannon() {
    if (image) {
        al_destroy_bitmap(image);
    }
}

bool Cannon::loadImage(const char* filename) {
    image = al_load_bitmap(filename);
    if (!image) {
        fprintf(stderr, "Failed to load %s\n", filename);
        return false;
    }
    return true;
}

void Cannon::rotateLeft() {
    angle -= 15.0f;
    if (angle < 30.0f) angle = 30.0f;
}

void Cannon::rotateRight() {
    angle += 15.0f;
    if (angle > 150.0f) angle = 150.0f;
}

void Cannon::draw() {
    if (image) {
        float cx = al_get_bitmap_width(image) / 2.0f;
        float cy = al_get_bitmap_height(image);

        al_draw_rotated_bitmap(image, cx, cy, x, y, (angle - 90) * PI / 180.0f, 0);

    }
}

float Cannon::getAngle() const {
    return angle;
}


int Cannon::getX() const {
    return x;
}

int Cannon::getY() const {
    return y;
}
