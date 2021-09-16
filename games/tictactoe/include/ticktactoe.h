#ifndef TICKTACTOE_H
#define TICKTACTOE_H

#include <game_interface.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


#define N 3
#define SCREEN_WIDTH 640.0
#define SCREEN_HEIGHT 480.0
#define CELL_WIDTH (SCREEN_WIDTH / N)
#define CELL_HEIGHT (SCREEN_HEIGHT / N)

typedef enum 
{
    empty,
    player_x,
    player_o
} tictactoe_player_t;

typedef enum 
{
    running = 0,
    player_x_won,
    player_o_won,
    tie,
    restart,
    quit
} tictactoe_states_t;

typedef struct
{    
    int board[N * N];
    tictactoe_player_t player;
    tictactoe_states_t state;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Sint32 row;
    Sint32 column;
    bool clicked;
    int last_frame_time;
} tictactoe_t;

/**
 * @brief 
 * 
 * @param object 
 * @return true 
 * @return false 
 */
bool tictactoe_init(void *object);

/**
 * @brief 
 * 
 * @param object 
 * @return true 
 * @return false 
 */
bool tictactoe_input(void *object);

/**
 * @brief 
 * 
 * @param object 
 * @return true 
 * @return false 
 */
bool tictactoe_update(void *object);

/**
 * @brief 
 * 
 * @param object 
 * @return true 
 * @return false 
 */
bool tictactoe_collision(void *object);

/**
 * @brief 
 * 
 * @param object 
 * @return true 
 * @return false 
 */
bool tictactoe_draw(void *object);

/**
 * @brief 
 * 
 * @param object 
 * @return true 
 * @return false 
 */
bool tictactoe_destroy(void *object);


/**
 * @brief 
 * 
 * @return game_base_t* 
 */
game_base_t *game_builder(void);

#endif /* TICKTACTOE_H */
