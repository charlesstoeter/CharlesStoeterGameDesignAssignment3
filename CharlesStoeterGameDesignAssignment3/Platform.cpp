#include "Platform.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>  // For drawing primitives
#include <iostream>


Platform::Platform(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), damageLevel(0) {
}

void Platform::draw() const {
    // Color gets lighter with damage: 0 = dark gray, 5 = light gray
    int brightness = 60 + damageLevel * 30;
    ALLEGRO_COLOR color = al_map_rgb(brightness, brightness, brightness);
    al_draw_filled_rectangle(x, y, x + width, y + height, color);
}



bool Platform::isGameOver() const {
    return damageLevel >= 5;
}


int Platform::getX() const { 
    return x;
}


int Platform::getY() const {
    return y; 
}


int Platform::getWidth() const {
    return width; 
}


int Platform::getHeight() const { 
    return height; 
}


void Platform::damage() {
    if (damageLevel < 5)
        damageLevel++;
}
