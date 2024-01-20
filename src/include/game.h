#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "brick.h"
#include <stdlib.h>
#include <stdio.h>

extern const int WIDTH;
extern const int HEIGHT;

#define TITLE "Brick Breaker"
#define FPS 60
#define SIZE_MULTIPLIER 2

#define ROWS 8
#define COLS 10

#define PADDLE_SPEED 320.0f
#define BALL_MAX_SPEED 400.0f

extern bool DEBUG;
extern bool game_over;

//main
void init();
void update();
void late_update();
void end();


// functionality
Vector2 normalize(Vector2 vec);
float clamp(float value, float min, float max);
void handle_map(const char* file_path, Brick* bricks[][ROWS]);
void restart();

#endif