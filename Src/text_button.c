#define _CRT_SECURE_NO_WARNINGS

#include "text_button.h"
#include "utility.h"
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * text
 * left up x, y
 * boarder w, h
 * color
 * hovered color (auto calculation)
 *
 */
TextButton textButton_create(float x, float y, float w, float h, const char* text, ALLEGRO_COLOR color){

    TextButton button;
    memset(&button, 0, sizeof(TextButton));

    button.body.x = x;
    button.body.y = y;
    button.body.w = w;
    button.body.h = h;
    button.text = text;
    button.color = color;

    // some default style settings
    button.font = menuFont;
    button.rounded = 2;
    button.thickness = 4;

    unsigned char r, g, b;
    al_unmap_rgb(color, &r, &g, &b);
    r = max(0, r - 100);
    g = max(0, g - 100);
    b = max(0, b - 100);
    button.hovered_color = al_map_rgb(r, g, b);
    return button;
}

void drawTextButton(TextButton *button) {
    double x = button->body.x, y = button->body.y, w = button->body.w, h = button->body.h;
    double cx = (2 * x + w)/2;
    double cy = (2 * y + h)/2;

    ALLEGRO_COLOR color_now = button->hovered? button->hovered_color : button->color;
    al_draw_text(button->font, color_now, cx, cy - al_get_font_ascent(button->font)/2, ALLEGRO_ALIGN_CENTRE, button->text);
    al_draw_rounded_rectangle(x, y, x + w, y + h, button->rounded, button->rounded, color_now, button->thickness);
}

void checkTextButtonHovered(TextButton *button, int mouse_x, int mouse_y){
    button->hovered = pnt_in_rect(mouse_x, mouse_y, button->body);
}