#include <game_interface.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define SDL2_CALLING_INIT       "Calling test init"
#define SDL2_CALLING_INPUT      "Calling test input"
#define SDL2_CALLING_UPDATE     "Calling test update"
#define SDL2_CALLING_COLLISION  "Calling test collision"
#define SDL2_CALLING_DRAW       "Calling test draw"


#define SDL2_SCREEN_WIDTH 480
#define SDL2_SCREEN_HIGHT 700

#define SDL2_IMAGE_PATH         "/media/cssouza/SOLIDCRIS/repositories/Faz-Em-C/spaceship/assets/imagens/Nave.png"
#define SDL2_IMAGE_EXPLOSION_PATH         "/media/cssouza/SOLIDCRIS/repositories/Faz-Em-C/spaceship/assets/imagens/Explosao.png"

static bool test_init(void *object);
static bool test_input(void *object);
static bool test_update(void *object);
static bool test_collision(void *object);
static bool test_draw(void *object);
static bool test_destroy(void *object);

static bool explosion_animation(void);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
SDL_Rect src_rect;
SDL_Rect dest_rect;

int main(int argc, char *argv[])
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
    int image_type = IMG_INIT_PNG;
    int image_ret;
    SDL_Surface *surface = NULL;
    // SDL_Rect src_rect;
    // SDL_Rect dest_rect;


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

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == NULL)
            break;

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        image_ret = IMG_Init(image_type);
        if(!(image_ret & image_type))
            break;

        // surface = IMG_Load(SDL2_IMAGE_PATH);
        surface = IMG_Load(SDL2_IMAGE_EXPLOSION_PATH);
        
        if(surface == NULL)
            break;

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if(texture == NULL)
            break;

        SDL_FreeSurface(surface);

        // SDL_QueryTexture(texture, NULL, NULL, &src_rect.w, &src_rect.h);

        // printf("width = %d, height = %d\n", src_rect.w, src_rect.h);

        src_rect.w = 192;
        src_rect.h = 192;

        dest_rect.x = src_rect.x = 0;
        dest_rect.y = src_rect.y = 0;
        dest_rect.w = src_rect.w;
        dest_rect.h = src_rect.h;

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
    return explosion_animation();
}

static bool test_collision(void *object)
{
    printf("%s\n", SDL2_CALLING_COLLISION);
    return true;
}

static bool test_draw(void *object)
{
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, texture, &src_rect, &dest_rect);

    SDL_RenderPresent(renderer);

    SDL_Delay(50);
    return true;
}

static bool test_destroy(void *object)
{

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );    

    IMG_Quit();
	SDL_Quit();
    return true;
}

static bool explosion_animation(void)
{
    bool state = true;
    static int value_x = 0;
    static int value_y = 0;
    if(value_x < 5)
    {
        src_rect.x = 192 * ((SDL_GetTicks() / 100) % 6);
        src_rect.y = 192 * value_y;
        value_x++;
    }
    else 
    {
        value_x = 0;
        src_rect.x = 0;
        value_y++;
        if(value_y > 6)
        {
            value_y = 0;
            state = false;
        }        
    }

    return state;
}