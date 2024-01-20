#ifndef PADDLE_H
#define PADDLE_H

#include "raylib.h"
#include <stdlib.h>


typedef struct Paddle
{
    enum
    {
        SMALL,
        MEDIUM,
        LARGE
    } type;
    
    Vector2 pos;
    Vector2 size;
    Texture2D tex;

} Paddle;

Paddle* init_paddle(int type, Vector2 pos);
void update_paddle(Paddle* paddle);
void draw_paddle(Paddle* paddle);
Rectangle get_paddle_rec(Paddle* paddle);

#endif