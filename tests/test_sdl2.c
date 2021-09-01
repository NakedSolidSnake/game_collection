#include <game_interface.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define SDL2_CALLING_INIT       "Calling test init"
#define SDL2_CALLING_INPUT      "Calling test input"
#define SDL2_CALLING_UPDATE     "Calling test update"
#define SDL2_CALLING_COLLISION  "Calling test collision"
#define SDL2_CALLING_DRAW       "Calling test draw"


#define SDL2_SCREEN_WIDTH 480
#define SDL2_SCREEN_HIGHT 700

static bool test_init(void *object);
static bool test_input(void *object);
static bool test_update(void *object);
static bool test_collision(void *object);
static bool test_draw(void *object);
static bool test_destroy(void *object);

SDL_Window *window = NULL;
SDL_Surface *surface = NULL;

int main()
{
    bool status = false;
    game_base_t test_game =
    {
        .init = test_init, 
        .input = test_input,
        .collision = test_collision,
        .update = test_update,
        .draw = test_draw,
        .destroy = test_destroy
    };

    if( game_loop(&test_game, NULL) == true)
        status = true;

    return status ? EXIT_SUCCESS : EXIT_FAILURE;
}


static bool test_init(void *object)
{
    bool status = false;

    do 
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
            break;

         window = SDL_CreateWindow("Title",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL2_SCREEN_WIDTH,
                              SDL2_SCREEN_HIGHT,
                              SDL_WINDOW_SHOWN);

        if(window == NULL)
            break;

        surface = SDL_GetWindowSurface(window);

        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

    } while(false);


    return status;
}

static bool test_input(void *object)
{
    printf("%s\n", SDL2_CALLING_INPUT);
    return true;
}

static bool test_update(void *object)
{
    SDL_UpdateWindowSurface(window);
    SDL_Delay( 2000 );
    return true;
}

static bool test_collision(void *object)
{
    printf("%s\n", SDL2_CALLING_COLLISION);
    return true;
}

static bool test_draw(void *object)
{
    printf("%s\n", SDL2_CALLING_DRAW);
    return false;
}

static bool test_destroy(void *object)
{
    SDL_DestroyWindow( window );

	SDL_Quit();
    return true;
}