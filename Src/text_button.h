#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H

#include "utility.h"
#include "shared.h"
#include "game.h"

typedef struct TextButton {
    RecArea body;
    bool hovered;
    const char *text;
    ALLEGRO_COLOR color;
    ALLEGRO_COLOR hovered_color;
    ALLEGRO_FONT *font;
    int rounded;
    int thickness;
} TextButton;

TextButton textButton_create(float x, float y, float w, float h, const char* text, ALLEGRO_COLOR color);
void drawTextButton(TextButton *button);
void checkTextButtonHovered(TextButton *button, int mouse_x, int mouse_y);

#endif
