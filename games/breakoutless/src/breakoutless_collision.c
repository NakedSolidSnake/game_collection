#include <breakoutless.h>

bool breakoutless_collision(void *object)
{
    breakoutless_t *breakoutless = (breakoutless_t *)object;
    if(breakoutless->start && breakoutless->game_over == false)
    {
        breakoutless_object_t *ball = &breakoutless->ball;   
        breakoutless_object_t *paddle = &breakoutless->paddle;

        printf("Collision.\n");
        if (ball->coord.x <= 0 || ball->coord.x + ball->dimension.width >= WINDOW_WIDTH)
        {
            ball->speed.vx = -ball->speed.vx;
            Mix_PlayChannel( -1, breakoutless->sound_wall, 0 );
        }

        if (ball->coord.y < 0)
        {
            ball->speed.vy = -ball->speed.vy;
            Mix_PlayChannel( -1, breakoutless->sound_wall, 0 );
        }

        // Check for ball collision with the paddle
        if (ball->coord.y + ball->dimension.height >= paddle->coord.y &&
            ball->coord.x + ball->dimension.width >= paddle->coord.x &&
            ball->coord.x <= paddle->coord.x + paddle->dimension.width)
        {
            ball->speed.vy = -ball->speed.vy;
            Mix_PlayChannel( -1, breakoutless->sound_paddle, 0 );
        }

        // Prevent paddle from moving outside the boundaries of the window
        if (paddle->coord.x <= 0)
            paddle->coord.x = 0;
        if (paddle->coord.x >= WINDOW_WIDTH - paddle->dimension.width)
            paddle->coord.x = WINDOW_WIDTH - paddle->dimension.width;

        // Check for game over
        if (ball->coord.y + ball->dimension.height > WINDOW_HEIGHT)
        {
            Mix_PlayChannel( -1, breakoutless->sound_ground, 0 );
            breakoutless->game_over = true;
            breakoutless->start = false;
            ball->coord.x = ball->coord.y = 0;
            ball->speed.vx = ball->speed.vy = BREAKOUTLESS_BALL_SPEED;
        }
    }
    return true;
}