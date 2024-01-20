#include "include/paddle.h"
#include "include/game.h"
#include <stdio.h>

Paddle* init_paddle(int type, Vector2 pos)
{
    Paddle* paddle = calloc(1, sizeof(Paddle));

    paddle->type = type;
    paddle->pos = pos;
    
    Texture2D texture;

    switch(paddle->type)
    {
        case SMALL:
            texture = LoadTexture("assets/paddle-s.png");
            break;
        case MEDIUM:
            texture = LoadTexture("assets/paddle-m.png");
            break;
        case LARGE:
            texture = LoadTexture("assets/paddle-l.png");
            break;
        default:
            printf("Error on initializing a paddle\n");
            break;
    }

    paddle->tex = texture;

    paddle->size = (Vector2){ .x = texture.width * SIZE_MULTIPLIER, .y = texture.height * SIZE_MULTIPLIER};

    return paddle;
}
void update_paddle(Paddle* paddle)
{
    if(IsMouseButtonDown(0) && DEBUG)
    {
        paddle->pos = GetMousePosition();
        printf("X: %0.2f, Y: %0.2f\n", paddle->pos.x, paddle->pos.y);
    }

    paddle->pos.x += (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * PADDLE_SPEED * GetFrameTime();

    if(paddle->pos.x <= 0)
    {
        paddle->pos.x = 0;
    }
    else if(paddle->pos.x + paddle->size.x >= WIDTH)
    {
        paddle->pos.x = WIDTH - paddle->size.x;
    }
}
void draw_paddle(Paddle* paddle)
{
    if(DEBUG) DrawRectangleRec(get_paddle_rec(paddle), RED);

    DrawTexturePro(paddle->tex, (Rectangle){ .x = 0, .y = 0, .width = paddle->tex.width, .height = paddle->tex.height},
    get_paddle_rec(paddle),
    (Vector2){ 0 }, 0, WHITE
    );
}
Rectangle get_paddle_rec(Paddle* paddle)
{
    return (Rectangle){ .x = paddle->pos.x, .y = paddle->pos.y, .width = paddle->size.x, .height = paddle->size.y };
}