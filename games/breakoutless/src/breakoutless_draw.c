#include <breakoutless.h>


static void breakoutless_draw_intro(void *object);
static void breakoutless_draw_game_over(void *object);
static void breakoutless_draw_points(void *object);
static void breakoutless_draw_speedup_message(void *object);

static void breakoutless_draw_ball(void *object);
static void breakoutless_draw_paddle(void *object);


bool breakoutless_draw(void *object)
{
    breakoutless_t * breakoutless = (breakoutless_t *)object;
    
    SDL_SetRenderDrawColor(breakoutless->renderer, 100, 100, 100, 255);
    SDL_RenderClear(breakoutless->renderer);

    if (breakoutless->start && breakoutless->game_over == false)
    {

        breakoutless_draw_ball(object);
        breakoutless_draw_paddle(object);

        if(breakoutless->speedup)
        {
            static int frames = 60;
            static int frames_count = 0;

            breakoutless_draw_speedup_message(object);

            if(frames_count++ > frames)
            {
                breakoutless->speedup = false;
                frames_count = 0;
            }
        }

        breakoutless_draw_points(object);

    }
   
    else if(breakoutless->game_over == false && breakoutless->start == false)
    {
        breakoutless_draw_intro(object);
    }

    else if (breakoutless->game_over)
    {
        breakoutless_draw_game_over(object);
    }
    SDL_RenderPresent(breakoutless->renderer);

    return true;  
}

static void breakoutless_draw_intro(void *object)
{
    breakoutless_t * breakoutless = (breakoutless_t *)object;

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

    if (Mix_PlayingMusic() == 0)
    {
        //Play the music
        Mix_PlayMusic(breakoutless->music_intro, -1);
    }
}

static void breakoutless_draw_game_over(void *object)
{
    breakoutless_t * breakoutless = (breakoutless_t *)object;

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
    snprintf(text, 120, "Max Points: %d", breakoutless->points);
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *font = TTF_RenderText_Blended(breakoutless->font, text, white);
    SDL_Rect font_rect = {WINDOW_WIDTH / 2 - (font->w / 2), dest_rect.h + 150, font->w, font->h};
    breakoutless->texture_label = SDL_CreateTextureFromSurface(breakoutless->renderer, font);

    SDL_RenderCopy(breakoutless->renderer, breakoutless->texture_label, NULL, &font_rect);
    SDL_FreeSurface(font);

    breakoutless->has_game_over_draw = true;
}

static void breakoutless_draw_points(void *object)
{
    breakoutless_t * breakoutless = (breakoutless_t *)object;
    SDL_Color white = {255, 255, 255, 255};

    char text[120] = "";

    snprintf(text, 120, "Points: %10d", breakoutless->points++);                
    SDL_Surface *font = TTF_RenderText_Blended(breakoutless->points_font, text, white);
    SDL_Rect font_rect = {WINDOW_WIDTH /2 -(font->w / 2), WINDOW_HEIGHT - 18, font->w, font->h};
    breakoutless->texture_label = SDL_CreateTextureFromSurface(breakoutless->renderer, font);

    SDL_RenderCopy(breakoutless->renderer, breakoutless->texture_label, NULL, &font_rect);
    SDL_FreeSurface(font);
}

static void breakoutless_draw_speedup_message(void *object)
{
    breakoutless_t * breakoutless = (breakoutless_t *)object;
    SDL_Color white = {255, 255, 255, 255};

    SDL_Surface *speedup_font = TTF_RenderText_Blended(breakoutless->speedup_font, "Speed UP!!!!", white);
    SDL_Rect speedup_font_rect = {WINDOW_WIDTH / 2 - (speedup_font->w / 2), WINDOW_HEIGHT / 2 - (speedup_font->h / 2), speedup_font->w, speedup_font->h};
    breakoutless->texture_speedup = SDL_CreateTextureFromSurface(breakoutless->renderer, speedup_font);

    SDL_RenderCopy(breakoutless->renderer, breakoutless->texture_speedup, NULL, &speedup_font_rect);
    SDL_FreeSurface(speedup_font);
}

static void breakoutless_draw_ball(void *object)
{
    breakoutless_t * breakoutless = (breakoutless_t *)object;
    breakoutless_object_t *ball = &breakoutless->ball;

    SDL_Rect ball_rect =
        {
            (int)ball->coord.x,
            (int)ball->coord.y,
            (int)ball->dimension.width,
            (int)ball->dimension.height};

    SDL_SetRenderDrawColor(breakoutless->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(breakoutless->renderer, &ball_rect);
}

static void breakoutless_draw_paddle(void *object)
{
    breakoutless_t * breakoutless = (breakoutless_t *)object;
    breakoutless_object_t *paddle = &breakoutless->paddle;

    SDL_Rect paddle_rect =
    {
        (int)paddle->coord.x,
        (int)paddle->coord.y,
        (int)paddle->dimension.width,
        (int)paddle->dimension.height
    };

    SDL_SetRenderDrawColor(breakoutless->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(breakoutless->renderer, &paddle_rect);
}
