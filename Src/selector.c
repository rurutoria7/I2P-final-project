#define _CRT_SECURE_NO_WARNINGS

#include "selector.h"
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
Selector selector_create(float x, float y, float w, float h, char **items, int item_num, int default_selection, ALLEGRO_COLOR color){

    Selector selector;
    memset(&selector, 0, sizeof(Selector));

    selector.body.x = x;
    selector.body.y = y;
    selector.body.w = w;
    selector.body.h = h;

    // triangle button layout
    double btn_w = 30, btn_h = btn_w * 0.866;
    double cx = (2 * x + w)/2;
    double one_third_y = y + h/3;
    double two_third_y = y + h*2/3;
    selector.btn_body[0].x = cx - btn_w/2;
    selector.btn_body[0].y = one_third_y - btn_h*1.5;
    selector.btn_body[0].w = btn_w;
    selector.btn_body[0].h = btn_h;
    selector.btn_body[1].x = cx - btn_w/2;
    selector.btn_body[1].y = two_third_y + btn_h*0.5;
    selector.btn_body[1].w = btn_w;
    selector.btn_body[1].h = btn_h;

    selector.items = items;
    selector.item_num = item_num;
    selector.now_selected = default_selection;
    selector.color = color;

    // some default style settings
    selector.font = menuFont;
    selector.rounded = 2;
    selector.thickness = 4;

    // auto calculate hovered_color
    unsigned char r, g, b;
    al_unmap_rgb(color, &r, &g, &b);
    r = max(0, r - 70);
    g = max(0, g - 70);
    b = max(0, b - 70);
    selector.hovered_color = al_map_rgb(r, g, b);
    return selector;
}

void drawSelector(Selector *selector) {
    double x = selector->body.x, y = selector->body.y, w = selector->body.w, h = selector->body.h;
    double cx = (2 * x + w)/2;
    double cy = (2 * y + h)/2;
    double one_third_y = y + h/3;
    double two_third_y = y + h*2/3;

    char *text_to_show = selector->items[selector->now_selected];

    ALLEGRO_COLOR color_now[2];
    color_now[0] = selector->hovered[0] ? selector->hovered_color : selector->color;
    color_now[1] = selector->hovered[1] ? selector->hovered_color : selector->color;

    al_draw_text(selector->font, selector->color, cx, cy - al_get_font_ascent(selector->font) / 2, ALLEGRO_ALIGN_CENTRE, text_to_show);
    al_draw_rounded_rectangle(x, one_third_y,
                              x + w, two_third_y,
                              selector->rounded, selector->rounded,
                              selector->color, selector->thickness);
    al_draw_filled_triangle(cx, selector->btn_body[0].y,
                            selector->btn_body[0].x, selector->btn_body[0].y + selector->btn_body[0].h,
                            selector->btn_body[0].x + selector->btn_body[0].w, selector->btn_body[0].y + selector->btn_body[0].h,
                            color_now[0]);
    al_draw_filled_triangle(cx, selector->btn_body[1].y + selector->btn_body[1].h,
                            selector->btn_body[1].x, selector->btn_body[1].y,
                            selector->btn_body[1].x + selector->btn_body[0].w, selector->btn_body[1].y,
                            color_now[1]);
}

void checkSelectorHovered(Selector *selector, int mouse_x, int mouse_y){
    selector->hovered[0] = pnt_in_rect(mouse_x, mouse_y, selector->btn_body[0]);
    selector->hovered[1] = pnt_in_rect(mouse_x, mouse_y, selector->btn_body[1]);
}

void selectorOnMouseDown(Selector *selector){
    if (selector->hovered[0]){
        if (selector->now_selected > 0){
            selector->now_selected--;
        }
    }
    if (selector->hovered[1]){
        if (selector->now_selected+1 < selector->item_num){
            selector->now_selected++;
        }
    }
}
