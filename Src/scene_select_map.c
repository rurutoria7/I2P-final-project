// DONE: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include "scene_select_map.h"
#include "game.h"
#include "text_button.h"
#include "selector.h"

static Selector map_selector;
static char *map_selections[3] = {"NTHU", "Avalon", "Aincrad"};
static TextButton go_btn;
static TextButton exit_btn;


static void init(){
    map_selector = selector_create(SCREEN_W * 2.0 / 5, SCREEN_H * 2.0 / 5, 200, 100, map_selections, 3, 0, al_map_rgb(240, 0, 240));
    exit_btn = textButton_create(SCREEN_W * 1.0 / 5, SCREEN_H * 4.0 / 5, 100, 50, "EXIT", al_map_rgb(150, 150, 150));
    go_btn = textButton_create(SCREEN_W * 4.0 / 5, SCREEN_H * 4.0 / 5, 100, 50, "EXIT", al_map_rgb(0, 230, 0));
}

static void draw(void ){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(menuFont, al_map_rgb(240, 240, 240), SCREEN_W * 1.0 / 5, SCREEN_H * 2.2 / 5, ALLEGRO_ALIGN_CENTRE, "Choose Map:");
    drawSelector(&map_selector);
    drawTextButton(exit_btn);
}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
    checkSelectorHovered(&map_selector, mouse_x, mouse_y);
    exit_btn.hovered = textButtonHover(exit_btn, mouse_x, mouse_y);
}

static void on_mouse_down() {
    selectorOnMouseDown(&map_selector);
}

// The only function that is shared across files.
Scene scene_select_map_create(void) {
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.initialize = &init;
    scene.name = "Select_maps";
    scene.draw = &draw;
    scene.on_mouse_move = &on_mouse_move;
    scene.on_mouse_down = &on_mouse_down;
    game_log("Select_maps scene created");
    return scene;
}