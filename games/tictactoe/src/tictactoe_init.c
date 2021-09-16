#include <ticktactoe.h>
#include <stdio.h>

bool tictactoe_init(void *object)
{
    bool status = true;
    tictactoe_t *tictactoe = (tictactoe_t *)object;
    (void)tictactoe;

    printf("%s\n", __FUNCTION__);

    do 
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
            break;
        }

        tictactoe->window = SDL_CreateWindow("Tic Tac Toe",
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              SCREEN_WIDTH,
                                              SCREEN_HEIGHT,                                          
                                              SDL_WINDOW_SHOWN);

        if (tictactoe->window == NULL)
        {
            fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
            break;
        }

         tictactoe->renderer = SDL_CreateRenderer(tictactoe->window, -1,
                                                SDL_RENDERER_ACCELERATED |
                                                SDL_RENDERER_PRESENTVSYNC);
        if (tictactoe->renderer == NULL)
        {
            fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
            break;
        }

        status = true;

    } while(false);

    return status;
}