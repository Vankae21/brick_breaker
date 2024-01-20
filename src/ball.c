#include "include/ball.h"
#include "include/brick.h"
#include "include/game.h"
#include <math.h>

Ball* init_ball(Vector2 pos, Texture2D tex, Vector2 dir)
{
    Ball* ball = calloc(1, sizeof(Ball));

    ball->pos = pos;
    ball->tex = tex;
    ball->dir = dir;
    ball->size = (Vector2){ .x = tex.width * SIZE_MULTIPLIER, .y = tex.height * SIZE_MULTIPLIER };

    return ball;
}
void update_ball(Ball* ball)
{
    ball->pos.x += ball->dir.x * BALL_MAX_SPEED * GetFrameTime();
    ball->pos.y += ball->dir.y * BALL_MAX_SPEED * GetFrameTime();
    
    if(ball->pos.x <= 0 || ball->pos.x + ball->size.x >= WIDTH) ball->dir.x *= -1;
    if(ball->pos.y <= 0) ball->dir.y *= -1;

    else if(ball->pos.y >= HEIGHT)
    {
        game_over = true;
    }
}
void draw_ball(Ball* ball)
{
    if(DEBUG) DrawRectangleRec(get_ball_rec(ball), BLUE);

    DrawTexturePro(ball->tex, (Rectangle){ .x = 0, .y = 0, .width = ball->tex.width, .height = ball->tex.height},
    get_ball_rec(ball),
    (Vector2){ 0 }, 0, WHITE
    );
}
Rectangle get_ball_rec(Ball* ball)
{
    return (Rectangle){ .x = ball->pos.x, .y = ball->pos.y, .width = ball->size.x, .height = ball->size.y };
}
void handle_ball_collision(Ball* ball, Rectangle rec)
{
    if(ball->pos.y > rec.y + rec.height || ball->pos.y + ball->size.y < rec.y
    || ball->pos.x > rec.x + rec.width || ball->pos.x + ball->size.x < rec.x
    )
        return;

    float recCenter = rec.x + rec.width / 2;
    float hitOffset = (ball->pos.x + ball->size.x / 2 - recCenter) / (rec.width / 2);

    if(ball->pos.x + ball->size.x/2 > rec.x + rec.width/2)
    {
        // printf("%0.2f\n", hitOffset);
        ball->dir.x = hitOffset;
    }
    else if(ball->pos.x + ball->size.x/2 < rec.x + rec.width/2)
    {
        // printf("%0.2f\n",hitOffset);
        ball->dir.x = hitOffset;
    }

    if(ball->pos.y + ball->size.y/2 > rec.y + rec.height/2)
    {
        ball->dir.y = 1;
    }
    else if(ball->pos.y + ball->size.y/2 < rec.y + rec.height/2)
    {
        ball->dir.y = -1;
    }

    ball->dir = normalize(ball->dir);
}

void handle_brick_collision(Ball* ball, Brick* brick)
{
    Rectangle rec = get_brick_rec(brick);

    if(ball->pos.y > rec.y + rec.height || ball->pos.y + ball->size.y < rec.y
    || ball->pos.x > rec.x + rec.width || ball->pos.x + ball->size.x < rec.x
    )
        return;

    float hitOffsetX = (ball->pos.x + ball->size.x / 2) - (rec.x + rec.width / 2);
    float hitOffsetY = (ball->pos.y + ball->size.y / 2) - (rec.y + rec.height / 2);

    // Determine the side of collision
    float absOffsetX = fabs(hitOffsetX);
    float absOffsetY = fabs(hitOffsetY);

    if (absOffsetX > absOffsetY) {
        // Horizontal collision (left or right)
        ball->dir.x *= -1;
    } else {
        // Vertical collision (top or bottom)
        ball->dir.y *= -1;
    }


    ball->dir = normalize(ball->dir);

    brick->is_active = false;
}