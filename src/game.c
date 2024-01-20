#include "include/game.h"
#include "include/paddle.h"
#include "include/ball.h"
#include "include/brick.h"
#include <math.h>
#include <time.h>

bool DEBUG = false;
bool game_over = false;

const int WIDTH = 800;
const int HEIGHT = 600;

Paddle* paddle = NULL;
Ball* ball = NULL;
Brick* bricks[COLS][ROWS];

bool start = false;

Vector2 ball_start_pos = { .x = 380, .y = 480 };
Vector2 paddle_start_pos = { .x = 340, .y = 540 };

void init()
{
    srand(time(0));

    paddle = init_paddle(LARGE, paddle_start_pos);
    ball = init_ball(ball_start_pos, LoadTexture("assets/ball.png"), (Vector2){ .x = 0, .y = 1});

    handle_map("assets/data.txt", bricks);




}
void update()
{
    if(IsKeyPressed(KEY_SPACE)) start = true;

    if(!start)
    {
        DrawText("Press SPACE to Start\nby Hüseyn Aga", 24, 400, 48, RAYWHITE);
        return;
    }
    else if(game_over)
    {
        DrawText("    Game is Over!\nPress R to Restart", 170, 400, 48, RAYWHITE);

        if(IsKeyPressed(KEY_R))
        {
            restart();
        }
        return;
    }

    update_paddle(paddle);

    update_ball(ball);
    handle_ball_collision(ball, get_paddle_rec(paddle));

    for(int i = 0; i < COLS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            if(bricks[i][j] == NULL) continue;
            if(!bricks[i][j]->is_active) continue;
            handle_brick_collision(ball, bricks[i][j]);
        }
    }
}
void late_update()
{
    draw_paddle(paddle);
    draw_ball(ball);

    for(int i = 0; i < COLS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            if(bricks[i][j] == NULL) continue;
            if(!bricks[i][j]->is_active) continue;
            draw_brick(bricks[i][j]);
        }
    }
}
void end()
{
    free(paddle);
    free(ball);

    for(int i = 0; i < COLS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            if(bricks[i][j] == NULL) continue;
            free(bricks[i][j]);
        }
    }
}

// functionality
Vector2 normalize(Vector2 vec)
{
    Vector2 result = { 0 };
    float length = sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length != 0.0f) {
        result.x = vec.x / length;
        result.y = vec.y / length;
    }

    return result;
}

float clamp(float value, float min, float max)
{
    if(value < min)
    {
        return min;
    }
    else if(value > max)
    {
        return max;
    }
    return value;
}

void handle_map(const char* file_path, Brick* bricks[][ROWS]) {
    FILE* file = fopen(file_path, "r");

    if (file == NULL) {
        perror("Error opening the file");
        exit(1);
    }

    char line[100];
    int row = 0;

    Vector2 pos = { .x = 8, .y = 16 };

    while (fgets(line, sizeof(line), file)) {
        pos.x = 8;
        printf("%s", line);

        for (int col = 0;line[col] != '\0'; col++) {
            switch (line[col]) {
                case '0':
                    break;
                case '1':
                    bricks[col][row] = init_brick(0, pos);
                    break;
                case '2':
                    bricks[col][row] = init_brick(1, pos);
                    break;
                case '3':
                    bricks[col][row] = init_brick(2, pos);
                    break;
                case '4':
                    bricks[col][row] = init_brick(3, pos);
                    break;
                case '5':
                    bricks[col][row] = init_brick(4, pos);
                    break;
                default:
                    perror("Error on handle_map function\n");
                    break;
            }
            pos.x += 80;
            printf("char: %c\n", line[col]);
        }
        pos.y += 48;
        row++;
    }

    fclose(file);
}

void restart()
{
    game_over = false;
    start = false;

    for(int i = 0; i < COLS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            if(bricks[i][j] == NULL) continue;
            bricks[i][j]->is_active = true;
        }
    }

    ball->pos = ball_start_pos;
    paddle->pos = paddle_start_pos;
}