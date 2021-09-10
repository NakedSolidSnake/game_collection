#include <game_interface.h>
#include <breakoutless.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

game_base_t *game_builder(void)
{   
    breakoutless_t *breakoutless = (breakoutless_t *)malloc(sizeof(breakoutless_t));
    if (breakoutless)
    {
        breakoutless_t breakoutless_temp =
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
                    .x = (WINDOW_WIDTH / 2) - (breakoutless_temp.paddle.dimension.width / 2),
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
            .has_logo_draw = false,
            .speedup = false
        };

        memcpy(breakoutless, &breakoutless_temp, sizeof(breakoutless_t));
    }

    game_base_t *game = (game_base_t *)malloc(sizeof(game_base_t));
    if(game)
    {
        game_base_t game_interface =
        {
            .game_object = breakoutless,
            .init = breakoutless_init, 
            .input = breakoutless_input,
            .collision = breakoutless_collision,
            .update = breakoutless_update,
            .draw = breakoutless_draw,
            .destroy = breakoutless_destroy
        };

        memcpy(game, &game_interface, sizeof(game_interface));
    }

    if(!game)
    {
        free(breakoutless);
    }

    return game;
}
