#include <breakoutless.h>

bool breakoutless_update(void *object)
{
    breakoutless_t * breakoutless = (breakoutless_t *)object;
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - breakoutless->last_frame_time);

    // Only delay if we are too fast too update this frame
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        SDL_Delay(time_to_wait);

    // Get a delta time factor converted to seconds to be used to update my objects
    float delta_time = (SDL_GetTicks() - breakoutless->last_frame_time) / 1000.0;

    // Store the milliseconds of the current frame
    breakoutless->last_frame_time = SDL_GetTicks();

    if (breakoutless->start && breakoutless->game_over == false)
    {
        printf("update.\n"); 
        breakoutless_object_t *ball = &breakoutless->ball;   
        breakoutless_object_t *paddle = &breakoutless->paddle;

        if(breakoutless->points == 1000 || breakoutless->points == 2000 || breakoutless->points == 3000 || breakoutless->points == 5000)
        {
            ball->speed.vx = ball->speed.vx * 1.2;
            ball->speed.vy = ball->speed.vy * 1.2;
            breakoutless->speedup = true;
        }

        // update ball and paddle position
        ball->coord.x += ball->speed.vx * delta_time;
        ball->coord.y += ball->speed.vy * delta_time;
        paddle->coord.x += paddle->speed.vx * delta_time;
        paddle->coord.y += paddle->speed.vy * delta_time;
        breakoutless->points++;
    }

    return true;
}

