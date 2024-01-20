#ifndef BRICK_H
#define BRICK_H
#include "raylib.h"
#include <stdlib.h>

typedef struct Brick
{

    enum
    {
        BRICK_BLUE,
        BRICK_GREEN,
        BRICK_PINK,
        BRICK_RED,
        BRICK_YELLOW
    } color;

    Vector2 pos;
    Vector2 size;
    Texture2D tex;

    bool is_active;

} Brick;

Brick* init_brick(int color, Vector2 pos);
void update_brick(Brick* brick);
void draw_brick(Brick* brick);
Rectangle get_brick_rec(Brick* brick);

#endif