#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <direct.h> // Required for _getcwd
#include <cstring>  // For C-style strings




const int SCREEN_W = 800;
const int SCREEN_H = 600;



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















    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        std::cerr << "Failed to create display.\n";
        return -1;
    }


    ALLEGRO_BITMAP* test = al_load_bitmap("earth.png"); //debuging
    if (!test) {
        std::cerr << "Failed to load earth.png\n";
        return -1;
    }


    ALLEGRO_BITMAP* fire = al_load_bitmap("fire.png");
    if (!fire) {
        std::cerr << "Failed to load fire.png\n";
        return -1;
    }




    al_clear_to_color(al_map_rgb(0, 0, 0)); // Black background

    al_draw_bitmap(fire, 100, 100, 0); // Draw the image at (100, 100)

    al_flip_display();// Show the result





    al_rest(3.0); // Pause for 3 seconds to view the image

    al_destroy_bitmap(fire);
    al_destroy_display(display);
    return 0;
}
