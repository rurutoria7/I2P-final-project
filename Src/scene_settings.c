// DONE: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include "scene_settings.h"
#include "scene_menu_object.h"
#include "game.h"

// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

static Button music_vol_down_btn;
static Button music_vol_up_btn;
static Button effect_vol_down_btn;
static Button effect_vol_up_btn;
static int music_volume_percentage;
static int effect_volume_percentage;

static ALLEGRO_BITMAP *volume_block;



// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.

static void init(){
    music_vol_down_btn = button_create(SCREEN_W * 1.05 / 5, SCREEN_H * 1.0 / 5, 50, 50, "Assets/volume_down.png", "Assets/volume_down.png");
    music_vol_up_btn = button_create(SCREEN_W * 3.3 / 5, SCREEN_H * 1.0 / 5, 50, 50, "Assets/volume_up.png", "Assets/volume_up.png");
    effect_vol_down_btn = button_create(SCREEN_W * 1.05 / 5, SCREEN_H * 3.0 / 5, 50, 50, "Assets/volume_down.png", "Assets/volume_down.png");
    effect_vol_up_btn = button_create(SCREEN_W * 3.3 / 5, SCREEN_H * 3.0 / 5, 50, 50, "Assets/volume_up.png", "Assets/volume_up.png");
    music_volume_percentage = 10;
    effect_volume_percentage = 10;
    volume_block = load_bitmap("Assets/volume_block.png");
}

static void draw(void ){
	al_clear_to_color(al_map_rgb(0, 0, 0));
    drawButton(music_vol_down_btn);
    drawButton(music_vol_up_btn);
    drawButton(effect_vol_down_btn);
    drawButton(effect_vol_up_btn);
    al_draw_text(
            menuFont,
            al_map_rgb(230, 230, 230),
            SCREEN_W/2.0, SCREEN_H * 0.5 / 5,
            ALLEGRO_ALIGN_CENTER,
            "MUSIC VOLUME"
    );
    for (int i = 0; i < music_volume_percentage; i++){
        al_draw_scaled_bitmap(volume_block,
                              0, 0,
                              18, 38,
                              SCREEN_W * 1.5 / 5 + SCREEN_W * 1.0 * i / 30,
                              SCREEN_H * 1.0 / 5 + 4,
                              18, 38,
                              0);
    }
    al_draw_text(
            menuFont,
            al_map_rgb(230, 230, 230),
            SCREEN_W/2.0, SCREEN_H * 2.5 / 5,
            ALLEGRO_ALIGN_CENTER,
            "EFFECT VOLUME"
    );
    for (int i = 0; i < effect_volume_percentage; i++){
        al_draw_scaled_bitmap(volume_block,
                              0, 0,
                              18, 38,
                              SCREEN_W * 1.5 / 5 + SCREEN_W * 1.0 * i / 30,
                              SCREEN_H * 3.0 / 5 + 4,
                              18, 38,
                              0);
    }

}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
    //	[HACKATHON 3-7]
    //	DONE: Update button's status(hovered), and utilize the function `pnt_in_rect`, which you just implemented
    //	Uncomment and fill the code below
    music_vol_down_btn.hovered = buttonHover(music_vol_down_btn, mouse_x, mouse_y);
    music_vol_up_btn.hovered = buttonHover(music_vol_up_btn, mouse_x, mouse_y);
    effect_vol_down_btn.hovered = buttonHover(effect_vol_down_btn, mouse_x, mouse_y);
    effect_vol_up_btn.hovered = buttonHover(effect_vol_up_btn, mouse_x, mouse_y);
}

static void on_mouse_down() {
    if (music_vol_down_btn.hovered){
        if (music_volume_percentage >= 1){
            music_volume_percentage -= 1;
        }
    }
    if (music_vol_up_btn.hovered){
        if (music_volume_percentage < 10){
            music_volume_percentage += 1;
        }
    }
    if (effect_vol_down_btn.hovered){
        if (effect_volume_percentage >= 1){
            effect_volume_percentage -= 1;
        }
    }
    if (effect_vol_up_btn.hovered){
        if (effect_volume_percentage < 10){
            effect_volume_percentage += 1;
        }
    }
    music_volume = DEFAULT_VOLUME * music_volume_percentage / 10;
    effect_volume = DEFAULT_VOLUME * effect_volume_percentage / 10;
    char c[100];
    sprintf(c, "music_volume = %d, effect_volume = %d", music_volume_percentage, effect_volume_percentage);
    game_log(c);
}

// The only function that is shared across files.
Scene scene_settings_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
    scene.initialize = &init;
	scene.name = "Settings";
	scene.draw = &draw;
    scene.on_mouse_move = &on_mouse_move;
    scene.on_mouse_down = &on_mouse_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	return scene;
}