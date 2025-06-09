#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <direct.h> // required for _getcwd
#include <cstring>  // for C-style strings
#include "Orb.h"
#include "Cannon.h"
#include "Asteroid.h"
#include "Platform.h"
#include <allegro5/allegro_primitives.h>  
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>  

#define PI 3.14159265

Asteroid asteroids[5];



const int SCREEN_W = 900;
const int SCREEN_H = 800;


Orb orbs[10];  // Up to 10 on screen



bool checkCollision(int x1, int y1, int w1, int h1,
    int x2, int y2, int w2, int h2) {
    return !(x1 + w1 < x2 ||     // Right of A is left of B
        x1 > x2 + w2 ||     // Left of A is right of B
        y1 + h1 < y2 ||     // Bottom of A is above B
        y1 > y2 + h2);      // Top of A is below B
}


int main() {



    char cwd[512];
    _getcwd(cwd, 512);
    std::cout << "Current working directory: " << cwd << std::endl;



    if (!al_init()) {
        std::cerr << "Failed to initialize Allegro.\n";
        return -1;
    }


	if (!al_init_image_addon()) {
		std::cerr << "Failed to initialize Allegro image addon.\n";
		return -1;
	}





	if (!al_install_keyboard()) {
		std::cerr << "Failed to install keyboard.\n";
		return -1;
	}

	if (!al_install_mouse()) {
		std::cerr << "Failed to install mouse.\n";
		return -1;
	}

    if (!al_init_font_addon()) {
        std::cerr << "Failed to initialize font addon.\n";
        return -1;
    }

    if (!al_init_ttf_addon()) {
        std::cerr << "Failed to initialize TTF addon.\n";
        return -1;
    }




    al_init_primitives_addon();





    ALLEGRO_FONT* gameFont = al_load_ttf_font("ARIAL.TTF", 36, 0); // Adjust size as needed
    if (!gameFont) {
        std::cerr << "Failed to load font.\n";
        return -1;
    }





    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        std::cerr << "Failed to create display.\n";
        return -1;
    }


    ALLEGRO_BITMAP* background = al_load_bitmap("earth.png");
    if (!background) {
        std::cerr << "Failed to load earth.png\n";
        return -1;
    }


    ALLEGRO_BITMAP* fire = al_load_bitmap("fire.png");
    if (!fire) {
        std::cerr << "Failed to load fire.png\n";
        return -1;
    }


    al_convert_mask_to_alpha(fire, al_map_rgb(255, 255, 255));





    Cannon cannon(SCREEN_W / 2, SCREEN_H - 100);
    if (!cannon.loadImage("cannon.png")) {
        std::cerr << "Could not load cannon image.\n";
        return -1;
    }


    for (int i = 0; i < 5; ++i) {
        asteroids[i].loadImage("astroid.png");
        asteroids[i].loadDestroyedImage("destroyed.png");
        al_convert_mask_to_alpha(asteroids[i].getBitmap(), al_map_rgb(255, 255, 255));

    }

    Platform platform(0, SCREEN_H - 50, SCREEN_W, 50); // Full-width platform at bottom


    


    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); // 60 FPS
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    al_start_timer(timer);

    bool gameOver = false;



    bool done = false;
    bool keys[ALLEGRO_KEY_MAX] = { false };

    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            done = true;
        }





        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            keys[ev.keyboard.keycode] = true;
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;





            // Fire orb on space
            if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                for (int i = 0; i < 10; i++) {
                    if (!orbs[i].isLive()) {
                        float angleRad = cannon.getAngle() * PI / 180.0f;
                        float fireX = cannon.getX() + 50 * cos(angleRad);
                        float fireY = cannon.getY() - 50 * sin(angleRad);
                        orbs[i].fire(fireX, fireY, cannon.getAngle(), fire);
                        break;
                    }
                }
            }

            if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
                cannon.rotateLeft();





            if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                cannon.rotateRight();




        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            keys[ev.keyboard.keycode] = false;
        }




        else if (ev.type == ALLEGRO_EVENT_TIMER) {
            // Update orbs
            for (int i = 0; i < 10; i++) {
                if (orbs[i].isLive()) {
                    orbs[i].update();
                }
            }

            if (platform.isGameOver()) {
                gameOver = true;
            }


            // Check orb-asteroid collisions
            for (int i = 0; i < 10; i++) {
                if (orbs[i].isLive()) {
                    for (int j = 0; j < 5; j++) {
                        if (asteroids[j].isLive()) {
                            if (checkCollision(
                                orbs[i].getX(), orbs[i].getY(), 16, 16, // Orb size
                                asteroids[j].getX(), asteroids[j].getY(),
                                asteroids[j].getBoundX(), asteroids[j].getBoundY()
                            )) {
                                orbs[i].deactivate();
                                asteroids[j].setDestroyed(true);
                                break;
                            }
                        }
                    }
                }
            }



            for (int i = 0; i < 5; ++i) {
                if (!asteroids[i].isLive()) {
                    if (rand() % 100 < 2) {
                        asteroids[i].start(SCREEN_W);
                        asteroids[i].setLive(true);
                        asteroids[i].setDestroyed(false); 
                    }
                }
                else {
                    asteroids[i].update(platform.getY(), platform.getHeight(), &platform);

                }
            }

            // Draw everything
            al_clear_to_color(al_map_rgb(0, 0, 0));

            



            al_draw_bitmap(background, 0, 0, 0);
            platform.draw();
            cannon.draw();
            for (int i = 0; i < 10; i++) {
                orbs[i].draw();
            }

            for (int i = 0; i < 5; ++i) {
                asteroids[i].draw();
            }

            if (gameOver) {
                al_draw_text(gameFont, al_map_rgb(255, 0, 0), SCREEN_W / 2, SCREEN_H / 2 - 50,
                    ALLEGRO_ALIGN_CENTER, "GAME OVER");
            }
           
            al_flip_display();
        }
    }



    al_destroy_bitmap(background);

    al_destroy_bitmap(fire);
    al_destroy_display(display);


    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    al_destroy_font(gameFont);

    return 0;
}






