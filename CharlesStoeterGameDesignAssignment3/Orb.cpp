#include "Orb.h"
#include <allegro5/allegro_primitives.h> // if you want to draw fallback circles
#include <cmath> // for cos/sin

#define PI 3.14159265 // Pi constant

Orb::Orb() {
    x = y = 0;
    speed = 10;
    radianAngle = 0;
    live = false;
    image = nullptr;
}

void Orb::fire(int startX, int startY, float angle, ALLEGRO_BITMAP* img) {
    if (!live) {

        x = startX;
        y = startY;



        radianAngle = angle * PI / 180.0f;




        speed = 10;
        image = img;
        live = true;
    }
}




void Orb::update() {
    if (!live) return;

    y -= speed * sin(radianAngle);
    x -= speed * cos(radianAngle);

    // Kill if off-screen
    if (x < 0 || x > 900 || y < 0 || y > 800) {
        live = false;
    }
}




void Orb::draw() {
    if (live && image) {
        float cx = al_get_bitmap_width(image) / 2.0f;
        float cy = al_get_bitmap_height(image); // assumes origin is bottom-center

        al_draw_rotated_bitmap(image, cx, cy, x, y, radianAngle - PI / 2, 0);
    }
}




void Orb::deactivate() {
    live = false;
}




bool Orb::isLive() const {
    return live;
}


int Orb::getX() const {
    return x;
}

int Orb::getY() const {
    return y;
}