#include <game_interface.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define BREAKOUTLESS_LOGO_PATH           "/media/cssouza/SOLIDCRIS/repositories/Faz-Em-C/spaceship/src/breakoutless/assets/breakoutless_logo.png"
#define BREAKOUTLESS_GAME_OVER_PATH      "/media/cssouza/SOLIDCRIS/repositories/Faz-Em-C/spaceship/src/breakoutless/assets/game_over.png"
#define BREAKOUTLESS_FONT_PATH           "/media/cssouza/SOLIDCRIS/repositories/Faz-Em-C/spaceship/src/breakoutless/assets/fonts/font.ttf"

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

#define BREAKOUTLESS_BALL_SPEED 300

typedef struct 
{
    float x;
    float y;
} point_t;

typedef struct 
{
    float width;
    float height;
} dimension_t;

typedef struct
{
    float vx;
    float vy;
} speed_t;

typedef struct 
{
    point_t coord;
    dimension_t dimension;
    speed_t speed;
} breakoutless_object_t;

typedef struct
{    
    breakoutless_object_t paddle;
    breakoutless_object_t ball;    
    bool running;
    bool start;
    bool game_over;
    bool has_game_over_draw;
    bool has_logo_draw;
    int last_frame_time;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture_logo;
    SDL_Texture *texture_game_over;
    SDL_Texture *texture_label;
    TTF_Font *font;
    TTF_Font *points_font;
    int points;
} breakoutless_t;

static bool breakoutless_init(void *object);
static bool breakoutless_input(void *object);
static bool breakoutless_update(void *object);
static bool breakoutless_collision(void *object);
static bool breakoutless_draw(void *object);
static bool breakoutless_destroy(void *object);

int main()
{
    bool status = false;
    game_base_t test_game =
    {
        .init = breakoutless_init, 
        .input = breakoutless_input,
        .collision = breakoutless_collision,
        .update = breakoutless_update,
        .draw = breakoutless_draw,
        .destroy = breakoutless_destroy
    };

    breakoutless_t breakoutless = 
    {
        .ball = 
        {
            .dimension = 
            {
                .width = 15,
                .height = 15
            },
            .coord = 
            {
                .x = 20,
                .y = 0
            },
            .speed = 
            {
                .vx = BREAKOUTLESS_BALL_SPEED,
                .vy = BREAKOUTLESS_BALL_SPEED
            }
        },
        .paddle = 
        {
            .dimension = 
            {
                .width = 100,
                .height = 20
            },
            .coord = 
            {
                .x = (WINDOW_WIDTH / 2) - (breakoutless.paddle.dimension.width / 2),
                .y = WINDOW_HEIGHT - 40
            },
            .speed = 
            {
                .vx = 0,
                .vy = 0
            }
        },

        .start = false,
        .game_over = false,
        .running = true,
        .last_frame_time = 0,
        .window = NULL,
        .renderer = NULL,
        .points = 0,
        .has_game_over_draw = false,
        .has_logo_draw = false
    };

    if( game_loop(&test_game, &breakoutless) == true)
        status = true;

    return status ? EXIT_SUCCESS : EXIT_FAILURE;
}

static bool breakoutless_init(void *object)
{
    int image_type = IMG_INIT_PNG;
    int image_ret;
    SDL_Surface *surface_logo = NULL;
    SDL_Surface *surface_game_over = NULL;
    breakoutless_t * breakoutless = (breakoutless_t *)object;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    breakoutless->window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS);
    if (!breakoutless->window)
    {
        fprintf(stderr, "Error creating SDL Window.\n");
        return false;
    }

    breakoutless->renderer = SDL_CreateRenderer(breakoutless->window, -1, 0);
    if (!breakoutless->renderer)
    {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return false;
    }

    image_ret = IMG_Init(image_type);
    if (!(image_ret & image_type))
    {
        fprintf(stderr, "Initialize image.\n");
        return false;
    }
        

    surface_logo = IMG_Load(BREAKOUTLESS_LOGO_PATH);
    if (surface_logo == NULL)
    {
        fprintf(stderr, "Error to create image surface.\n");
        return false;
    }

    breakoutless->texture_logo = SDL_CreateTextureFromSurface(breakoutless->renderer, surface_logo);
    if (breakoutless->texture_logo == NULL)
    {
        fprintf(stderr, "Error to create texture from surface.\n");
        return false;
    }

    surface_game_over = IMG_Load(BREAKOUTLESS_GAME_OVER_PATH);
    if (surface_game_over == NULL)
    {
        fprintf(stderr, "Error to create image surface.\n");
        return false;
    }

    breakoutless->texture_game_over = SDL_CreateTextureFromSurface(breakoutless->renderer, surface_game_over);
    if (breakoutless->texture_game_over == NULL)
    {
        fprintf(stderr, "Error to create texture from surface.\n");
        return false;
    }

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Error to initialize fonts.\n");
        return false;
    }

    breakoutless->font = TTF_OpenFont(BREAKOUTLESS_FONT_PATH, 48);
    if (breakoutless->font == NULL)
    {
        fprintf(stderr, "Error to open font.\n");
        return false;
    }

    breakoutless->points_font = TTF_OpenFont(BREAKOUTLESS_FONT_PATH, 18);
    if (breakoutless->font == NULL)
    {
        fprintf(stderr, "Error to open font.\n");
        return false;
    }

    SDL_FreeSurface(surface_logo);
    SDL_FreeSurface(surface_game_over);

    return true;
}

static bool breakoutless_input(void *object)
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

static bool breakoutless_update(void *object)
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

        switch (breakoutless->points)
        {
        case 2000:
            breakoutless->ball.speed.vx = breakoutless->ball.speed.vx * 1.2;
            breakoutless->ball.speed.vy = breakoutless->ball.speed.vy * 1.2;
            break;

        case 5000:
            breakoutless->ball.speed.vx = breakoutless->ball.speed.vx * 1.2;
            breakoutless->ball.speed.vy = breakoutless->ball.speed.vy * 1.2;
            break;

        case 7000:
            breakoutless->ball.speed.vx = breakoutless->ball.speed.vx * 1.2;
            breakoutless->ball.speed.vy = breakoutless->ball.speed.vy * 1.2;
            break;
        
        case 10000:
            breakoutless->ball.speed.vx = breakoutless->ball.speed.vx * 1.2;
            breakoutless->ball.speed.vy = breakoutless->ball.speed.vy * 1.2;
            break;       
        }

        // update ball and paddle position
        breakoutless->ball.coord.x += breakoutless->ball.speed.vx * delta_time;
        breakoutless->ball.coord.y += breakoutless->ball.speed.vy * delta_time;
        breakoutless->paddle.coord.x += breakoutless->paddle.speed.vx * delta_time;
        breakoutless->paddle.coord.y += breakoutless->paddle.speed.vy * delta_time;
        breakoutless->points++;
    }

    return true;
}

static bool breakoutless_collision(void *object)
{
    breakoutless_t * breakoutless = (breakoutless_t *)object;
    if(breakoutless->start && breakoutless->game_over == false)
    {
        printf("Collision.\n");
        if (breakoutless->ball.coord.x <= 0 || breakoutless->ball.coord.x + breakoutless->ball.dimension.width >= WINDOW_WIDTH)
            breakoutless->ball.speed.vx = -breakoutless->ball.speed.vx;
        if (breakoutless->ball.coord.y < 0)
            breakoutless->ball.speed.vy = -breakoutless->ball.speed.vy;

        // Check for ball collision with the paddle
        if (breakoutless->ball.coord.y + breakoutless->ball.dimension.height >= breakoutless->paddle.coord.y &&
            breakoutless->ball.coord.x + breakoutless->ball.dimension.width >= breakoutless->paddle.coord.x &&
            breakoutless->ball.coord.x <= breakoutless->paddle.coord.x + breakoutless->paddle.dimension.width)
            breakoutless->ball.speed.vy = -breakoutless->ball.speed.vy;

        // Prevent paddle from moving outside the boundaries of the window
        if (breakoutless->paddle.coord.x <= 0)
            breakoutless->paddle.coord.x = 0;
        if (breakoutless->paddle.coord.x >= WINDOW_WIDTH - breakoutless->paddle.dimension.width)
            breakoutless->paddle.coord.x = WINDOW_WIDTH - breakoutless->paddle.dimension.width;

        // Check for game over
        if (breakoutless->ball.coord.y + breakoutless->ball.dimension.height > WINDOW_HEIGHT)
        {
            breakoutless->game_over = true;
            breakoutless->start = false;
            breakoutless->ball.coord.x = breakoutless->ball.coord.y = 0;
            breakoutless->ball.speed.vx = breakoutless->ball.speed.vy = BREAKOUTLESS_BALL_SPEED;
        }
    }
    return true;
}

static bool breakoutless_draw(void *object)
{
    breakoutless_t * breakoutless = (breakoutless_t *)object;
    
    SDL_SetRenderDrawColor(breakoutless->renderer, 100, 100, 100, 255);
    SDL_RenderClear(breakoutless->renderer);

    if (breakoutless->start && breakoutless->game_over == false)
    {
        printf("Draw Game.\n");
        // Draw a rectangle for the ball object
        SDL_Rect ball_rect =
        {
            (int)breakoutless->ball.coord.x,
            (int)breakoutless->ball.coord.y,
            (int)breakoutless->ball.dimension.width,
            (int)breakoutless->ball.dimension.height
        };
        SDL_SetRenderDrawColor(breakoutless->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(breakoutless->renderer, &ball_rect);

        // Draw a rectangle for the paddle object
        SDL_Rect paddle_rect =
        {
            (int)breakoutless->paddle.coord.x,
            (int)breakoutless->paddle.coord.y,
            (int)breakoutless->paddle.dimension.width,
            (int)breakoutless->paddle.dimension.height
        };

        SDL_SetRenderDrawColor(breakoutless->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(breakoutless->renderer, &paddle_rect); 

        //draw points
        char text[120] = "";
        // int points = 200;
        snprintf(text, 120, "Points: %10d", breakoutless->points++);
        SDL_Color white = {255, 255, 255, 255};        
        SDL_Surface *font = TTF_RenderText_Blended(breakoutless->points_font, text, white);
        SDL_Rect font_rect = {WINDOW_WIDTH /2 -(font->w / 2), WINDOW_HEIGHT - 18, font->w, font->h};
        breakoutless->texture_label = SDL_CreateTextureFromSurface(breakoutless->renderer, font);

        SDL_RenderCopy(breakoutless->renderer, breakoutless->texture_label, NULL, &font_rect);
        SDL_FreeSurface(font);

    }
   
    //draw logo
    // else if(breakoutless->game_over == false && breakoutless->start == false && !breakoutless->has_logo_draw)
    else if(breakoutless->game_over == false && breakoutless->start == false)
    {
        printf("Draw Logo.\n");
        SDL_Rect src_rect;
        SDL_Rect dest_rect;
        SDL_QueryTexture(breakoutless->texture_logo, NULL, NULL, &src_rect.w, &src_rect.h);

        src_rect.x = 0;
        src_rect.y = 0;
        dest_rect.x = WINDOW_WIDTH / 2 - (src_rect.w / 2);
        dest_rect.y = WINDOW_HEIGHT / 2 - (src_rect.h / 2);
        dest_rect.w = src_rect.w;
        dest_rect.h = src_rect.h;

        SDL_RenderCopy(breakoutless->renderer, breakoutless->texture_logo, &src_rect, &dest_rect);

        SDL_Color white = {255, 255, 255, 255};
        SDL_Surface *font = TTF_RenderText_Blended(breakoutless->font, "Press Start", white);
        SDL_Rect font_rect = {WINDOW_WIDTH / 2 - (font->w / 2), dest_rect.y + 200, font->w, font->h};
        breakoutless->texture_label = SDL_CreateTextureFromSurface(breakoutless->renderer, font);

        SDL_RenderCopy(breakoutless->renderer, breakoutless->texture_label, NULL, &font_rect);
        SDL_FreeSurface(font);

        // breakoutless->has_logo_draw = true;
    }
    // else if (breakoutless->game_over && breakoutless->has_game_over_draw == false)
    else if (breakoutless->game_over)
    {
        //game over
        printf("Draw Game Over.\n");
        SDL_Rect src_rect;
        SDL_Rect dest_rect;
        SDL_QueryTexture(breakoutless->texture_game_over, NULL, NULL, &src_rect.w, &src_rect.h);

        src_rect.x = 0;
        src_rect.y = 0;
        dest_rect.x = WINDOW_WIDTH / 2 - (src_rect.w / 2);
        dest_rect.y = WINDOW_HEIGHT / 2 - (src_rect.h / 2);
        dest_rect.w = src_rect.w;
        dest_rect.h = src_rect.h;

        SDL_RenderCopy(breakoutless->renderer, breakoutless->texture_game_over, &src_rect, &dest_rect);

        char text[120] = "";
        // int points = 200;
        snprintf(text, 120, "Max Points: %d", breakoutless->points);
        SDL_Color white = {255, 255, 255, 255};
        SDL_Surface *font = TTF_RenderText_Blended(breakoutless->font, text, white);
        SDL_Rect font_rect = {WINDOW_WIDTH / 2 - (font->w / 2), dest_rect.h + 150, font->w, font->h};
        breakoutless->texture_label = SDL_CreateTextureFromSurface(breakoutless->renderer, font);

        SDL_RenderCopy(breakoutless->renderer, breakoutless->texture_label, NULL, &font_rect);
        SDL_FreeSurface(font);

        breakoutless->has_game_over_draw = true;
    }
    SDL_RenderPresent(breakoutless->renderer);

    return true;
}

static bool breakoutless_destroy(void *object)
{
    breakoutless_t * breakoutless = (breakoutless_t *)object;

    if(breakoutless->texture_label != NULL)
        SDL_DestroyTexture(breakoutless->texture_label);
    TTF_CloseFont(breakoutless->font);

    TTF_CloseFont(breakoutless->points_font);

    SDL_DestroyTexture(breakoutless->texture_logo);
    SDL_DestroyTexture(breakoutless->texture_game_over);

    SDL_DestroyRenderer(breakoutless->renderer);
    SDL_DestroyWindow(breakoutless->window);

    TTF_Quit();
    SDL_Quit();

    return true;
}