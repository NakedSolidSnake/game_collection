#include <game_interface.h>
#include <ticktactoe.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

game_base_t *game_builder(void)
{   
    tictactoe_t *tictactoe = (tictactoe_t *)malloc(sizeof(tictactoe_t));
    
    game_base_t *game = (game_base_t *)malloc(sizeof(game_base_t));
    if(game)
    {
        game_base_t game_interface =
        {
            .game_object = tictactoe,
            .init = tictactoe_init, 
            .input = tictactoe_input,
            .collision = tictactoe_collision,
            .update = tictactoe_update,
            .draw = tictactoe_draw,
            .destroy = tictactoe_destroy
        };

        memcpy(game, &game_interface, sizeof(game_interface));
    }

    if(!game)
    {
        free(tictactoe);
    }

    return game;
}
