#include "include/brick.h"
#include "include/game.h"
#include <stdio.h>

Brick* init_brick(int color, Vector2 pos)
{
    Brick* brick = calloc(1, sizeof(Brick));

    brick->color = color;
    brick->pos = pos;

    Texture2D texture;

    switch(brick->color)
    {
        case BRICK_BLUE:
            texture = LoadTexture("assets/blue.png");
            break;
        case BRICK_GREEN:
            texture = LoadTexture("assets/green.png");
            break;
        case BRICK_PINK:
            texture = LoadTexture("assets/pink.png");
            break;
        case BRICK_RED:
            texture = LoadTexture("assets/red.png");
            break;
        case BRICK_YELLOW:
            texture = LoadTexture("assets/yellow.png");
            break;
        default:
            printf("Error on initializing a brick\n");
            break;
    }

    brick->tex = texture;

    brick->size = (Vector2){ .x = texture.width * SIZE_MULTIPLIER, .y = texture.height / 4 * SIZE_MULTIPLIER};

    brick->is_active = true;

    return brick;
}
void update_brick(Brick* brick)
{

}
void draw_brick(Brick* brick)
{
    DrawTexturePro(brick->tex, (Rectangle){ .x = 0, .y = 0, .width = brick->tex.width, .height = brick->tex.height / 4},
    get_brick_rec(brick),
    (Vector2){ 0 }, 0, WHITE
    );
}
Rectangle get_brick_rec(Brick* brick)
{
    return (Rectangle){ .x = brick->pos.x, .y = brick->pos.y, .width = brick->size.x, .height = brick->size.y };
}