#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_settings.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "scene_game_over.h"
#include "utility.h"
#include "shared.h"


static void init() {
}

static void draw() {

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(
            menuFont,
            al_map_rgb(255, 255, 255),
            SCREEN_W/2,
            SCREEN_H - 75,
            ALLEGRO_ALIGN_CENTER,
            "GAME OVER"
    );
    al_draw_text(
            menuFont,
            al_map_rgb(255, 255, 255),
            SCREEN_W/2,
            SCREEN_H - 150,
            ALLEGRO_ALIGN_CENTER,
            "PRESS \"ENTER\" TO GO BACK TO MENU"
    );
}

static void destroy() {
}

static void on_key_down(int keycode) {

    switch (keycode) {
        case ALLEGRO_KEY_ENTER:
            game_change_scene(scene_menu_create());
            break;
        default:
            break;
    }
}

Scene scene_game_over_create() {

    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.name = "Game Over";
    scene.initialize = &init;
    scene.draw = &draw;
    scene.destroy = &destroy;
    scene.on_key_down = &on_key_down;
    // ------------------------------------

    game_log("Game-over scene created");
    return scene;
}