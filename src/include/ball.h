#ifndef BALL_H
#define BALL_H
#include "raylib.h"
#include "brick.h"
#include <stdlib.h>

typedef struct Ball
{

    Vector2 pos;
    Vector2 size;
    Texture2D tex;
    Vector2 dir;

} Ball;

Ball* init_ball(Vector2 pos, Texture2D tex, Vector2 dir);
void update_ball(Ball* ball);
void draw_ball(Ball* ball);
Rectangle get_ball_rec(Ball* ball);
void handle_ball_collision(Ball* ball, Rectangle rec);
void handle_brick_collision(Ball* ball, Brick* brick);

#endif