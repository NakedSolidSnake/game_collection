#include <breakoutless.h>

bool breakoutless_input(void *object)
{
    breakoutless_t * breakoutless = (breakoutless_t *)object;
    SDL_Event event;

    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        breakoutless->running = false;
        break;
    case SDL_KEYDOWN: // happens when presses the key
        if (event.key.keysym.sym == SDLK_ESCAPE)
            breakoutless->running = false;
        if (event.key.keysym.sym == SDLK_LEFT)
            breakoutless->paddle.speed.vx = -400;
        if (event.key.keysym.sym == SDLK_RIGHT)
            breakoutless->paddle.speed.vx = +400;        
        if (event.key.keysym.sym == SDLK_RETURN)
        {
            if(breakoutless->start == false)
            {
                breakoutless->game_over = false;  
                breakoutless->points = 0;          
                breakoutless->start = true;
                Mix_PauseMusic();
            }            
        }

        break;

    case SDL_KEYUP: // happens when releases the key
        if (event.key.keysym.sym == SDLK_LEFT)
            breakoutless->paddle.speed.vx = 0;
        if (event.key.keysym.sym == SDLK_RIGHT)
            breakoutless->paddle.speed.vx = 0;
        break;
    }

    return breakoutless->running;
}
