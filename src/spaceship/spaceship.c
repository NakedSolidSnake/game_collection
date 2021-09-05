#include <game_interface.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define SDL2_SCREEN_WIDTH 480
#define SDL2_SCREEN_HIGHT 700

#define SDL2_IMAGE_PATH         "/media/cssouza/SOLIDCRIS/repositories/Faz-Em-C/spaceship/assets/imagens/Nave.png"

typedef struct 
{
    unsigned int x;
    unsigned int y;
} point_t;

typedef struct
{
    point_t point;    
    bool is_running;
} spaceship_game_t;



static bool spaceship_init(void *object);
static bool spaceship_input(void *object);
static bool spaceship_update(void *object);
static bool spaceship_collision(void *object);
static bool spaceship_draw(void *object);
static bool spaceship_destroy(void *object);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
SDL_Rect src_rect;
SDL_Rect dest_rect;

int main()
{
     bool status = false;
    game_base_t test_game =
    {
        .init = spaceship_init, 
        .input = spaceship_input,
        .collision = spaceship_collision,
        .update = spaceship_update,
        .draw = spaceship_draw,
        .destroy = spaceship_destroy
    };

    spaceship_game_t spaceship = 
    {
        .is_running = true
    };

    if( game_loop(&test_game, &spaceship) == true)
        status = true;

    return status ? EXIT_SUCCESS : EXIT_FAILURE;
}

static bool spaceship_init(void *object)
{
    bool status = false;
    int image_type = IMG_INIT_PNG;
    int image_ret;
    SDL_Surface *surface = NULL;
    spaceship_game_t *spaceship = (spaceship_game_t *)object;
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

        surface = IMG_Load(SDL2_IMAGE_PATH);
        if(surface == NULL)
            break;

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if(texture == NULL)
            break;

        SDL_FreeSurface(surface);

        SDL_QueryTexture(texture, NULL, NULL, &src_rect.w, &src_rect.h);

        dest_rect.x = src_rect.x = spaceship->point.x = 0;
        dest_rect.y = src_rect.y = spaceship->point.y = 0;
        dest_rect.w = src_rect.w;
        dest_rect.h = src_rect.h;

    } while(false);


    return status;
}

static bool spaceship_input(void *object)
{
    SDL_Event event;
    spaceship_game_t *spaceship = (spaceship_game_t *)object;

    if(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            ((spaceship_game_t *)object)->is_running = false;
            break;

        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_UP)
            {
                spaceship->point.y -= 10;
            }

            if(event.key.keysym.sym == SDLK_DOWN)
            {
                spaceship->point.y += 10;
            }

            if(event.key.keysym.sym == SDLK_LEFT)
            {
                spaceship->point.x -= 10;
            }

            if(event.key.keysym.sym == SDLK_RIGHT)
            {
                spaceship->point.x += 10;
            }
            
            // switch (event.key.keysym.sym)
            // {
            // case SDLK_UP:
            //     printf("UP\n");
            //     spaceship->point.y -= 10;
            //     break;

            // case SDLK_DOWN:
            //     printf("Down\n");
            //     spaceship->point.y += 10;
            //     break;

            // case SDLK_LEFT:
            //     printf("Left\n");
            //     spaceship->point.x -= 10;
            //     break;

            // case SDLK_RIGHT:
            //     printf("Right\n");
            //     spaceship->point.x += 10;
            //     break;            
            // }
            break;
        
        default:
            break;
        }
    }

    return true;
}


static bool spaceship_update(void *object)
{
    bool state = true;
    spaceship_game_t *spaceship = (spaceship_game_t *)object;
    if(spaceship->is_running == false)
        state = false;

    dest_rect.x = spaceship->point.x;
    dest_rect.y = spaceship->point.y;
    
    return state;
}

static bool spaceship_collision(void *object)
{
    return true;
}

static bool spaceship_draw(void *object)
{
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, texture, &src_rect, &dest_rect);

    SDL_RenderPresent(renderer);
    return true;
}


static bool spaceship_destroy(void *object)
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );    

    IMG_Quit();
	SDL_Quit();
    return true;
}