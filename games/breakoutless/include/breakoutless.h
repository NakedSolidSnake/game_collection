#ifndef BREAKOUTLESS_H
#define BREAKOUTLESS_H

#include <game_interface.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define BREAKOUTLESS_LOGO_PATH           "/media/cssouza/SOLIDCRIS/repositories/Faz-Em-C/spaceship/games/breakoutless/assets/breakoutless_logo.png"
#define BREAKOUTLESS_GAME_OVER_PATH      "/media/cssouza/SOLIDCRIS/repositories/Faz-Em-C/spaceship/games/breakoutless/assets/game_over.png"
#define BREAKOUTLESS_FONT_PATH           "/media/cssouza/SOLIDCRIS/repositories/Faz-Em-C/spaceship/games/breakoutless/assets/fonts/font.ttf"


#define BREAKOUTLESS_INTRO_MUSIC         "/media/cssouza/SOLIDCRIS/repositories/Faz-Em-C/spaceship/games/breakoutless/assets/sounds/Gigakoops - Intro.mp3"
#define BREAKOUTLESS_GAME_OVER_MUSIC     "/media/cssouza/SOLIDCRIS/repositories/Faz-Em-C/spaceship/games/breakoutless/assets/sounds/Plusplus - Game Over.mp3"
#define BREAKOUTLESS_WALL_SOUND          "/media/cssouza/SOLIDCRIS/repositories/Faz-Em-C/spaceship/games/breakoutless/assets/sounds/hit_the_wall.wav"
#define BREAKOUTLESS_PADDLE_SOUND        "/media/cssouza/SOLIDCRIS/repositories/Faz-Em-C/spaceship/games/breakoutless/assets/sounds/hit_the_paddle.wav"
#define BREAKOUTLESS_GROUND_SOUND        "/media/cssouza/SOLIDCRIS/repositories/Faz-Em-C/spaceship/games/breakoutless/assets/sounds/hit_the_ground.wav"

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
    SDL_Texture *texture_speedup;
    TTF_Font *font;
    TTF_Font *points_font;
    TTF_Font *speedup_font;
    bool speedup;
    Mix_Music *music_intro;    
    int points;
    Mix_Chunk *sound_wall;
    Mix_Chunk *sound_paddle;
    Mix_Chunk *sound_ground;
} breakoutless_t;

/**
 * @brief 
 * 
 * @param object 
 * @return true 
 * @return false 
 */
bool breakoutless_init(void *object);

/**
 * @brief 
 * 
 * @param object 
 * @return true 
 * @return false 
 */
bool breakoutless_input(void *object);

/**
 * @brief 
 * 
 * @param object 
 * @return true 
 * @return false 
 */
bool breakoutless_update(void *object);

/**
 * @brief 
 * 
 * @param object 
 * @return true 
 * @return false 
 */
bool breakoutless_collision(void *object);

/**
 * @brief 
 * 
 * @param object 
 * @return true 
 * @return false 
 */
bool breakoutless_draw(void *object);

/**
 * @brief 
 * 
 * @param object 
 * @return true 
 * @return false 
 */
bool breakoutless_destroy(void *object);


/**
 * @brief 
 * 
 * @return game_base_t* 
 */
game_base_t *game_builder(void);

#endif /* BREAKOUTLESS_H */
