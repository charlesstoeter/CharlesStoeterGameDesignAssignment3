#include "Asteroid.h"
#include <allegro5/allegro.h>
#include <cstdlib>  // for rand()
#include <iostream>

Asteroid::Asteroid() {
    x = y = speed = 0;
    boundX = 32;
    boundY = 32;
    live = false;
    image = nullptr;
}

Asteroid::~Asteroid() {
    if (image) {
        al_destroy_bitmap(image);
        image = nullptr;

    }
}

void Asteroid::start(int screenW) {
    x = rand() % (screenW - boundX);
    y = 0;
    speed = 2 + rand() % 3;
    live = true;
}

void Asteroid::update() {
    if (live) {
        y += speed;
        if (y > 800) live = false;  // Off screen
    }
}

void Asteroid::draw() {
    if (live && image) {
        al_draw_bitmap(image, x, y, 0);
    }
}

void Asteroid::collideWithGround() {
    // Placeholder for logic if you want game over on ground hit
    live = false;
}

void Asteroid::setLive(bool l) { live = l; }
bool Asteroid::isLive() const { return live; }
int Asteroid::getX() const { return x; }
int Asteroid::getY() const { return y; }
int Asteroid::getBoundX() const { return boundX; }
int Asteroid::getBoundY() const { return boundY; }


void Asteroid::loadImage(const char* filename) {
    image = al_load_bitmap(filename);
    if (!image) {
        std::cerr << "Failed to load asteroid image: " << filename << "\n";
    }
}