#include <ticktactoe.h>
#include <stdio.h>
#include <SDL2/SDL2_gfxPrimitives.h>

static void tictactoe_draw_state(void *object);
static void tictactoe_draw_grid(void *object, const SDL_Color *color);
static void tictactoe_draw_x(void *object, int row, int column, const SDL_Color *color);
static void tictactoe_draw_o(void *object, int row, int column, const SDL_Color *color);
static void tictactoe_draw_board(void *object, const SDL_Color *player_x_color, const SDL_Color *player_o_color);
static void tictactoe_draw_running_state(void *object, const SDL_Color *color);
static void tictactoe_draw_game_over_state(void *object, const SDL_Color *color);

const SDL_Color GRID_COLOR = { .r = 255, .g = 255, .b = 255 };
const SDL_Color PLAYER_X_COLOR = { .r = 255, .g = 50, .b = 50 };
const SDL_Color PLAYER_O_COLOR = { .r = 50, .g = 100, .b = 255 };
const SDL_Color TIE_COLOR = { .r = 100, .g = 100, .b = 100 };

bool tictactoe_draw(void *object)
{
    bool status = true;
    tictactoe_t *tictactoe = (tictactoe_t *)object;

    SDL_SetRenderDrawColor(tictactoe->renderer, 0, 0, 0, 255);
    SDL_RenderClear(tictactoe->renderer);
    tictactoe_draw_state(tictactoe);
    SDL_RenderPresent(tictactoe->renderer);
    return status;
}

static void tictactoe_draw_state(void *object)
{
    tictactoe_t *tictactoe = (tictactoe_t *)object;

    switch (tictactoe->state) {
    case running:
        tictactoe_draw_running_state(object, &GRID_COLOR);
        break;

    case player_x_won:
        // render_game_over_state(renderer, game, &PLAYER_X_COLOR);
        tictactoe_draw_game_over_state(object, &PLAYER_X_COLOR);
        break;

    case player_o_won:
        // render_game_over_state(renderer, game, &PLAYER_O_COLOR);
        tictactoe_draw_game_over_state(object, &PLAYER_O_COLOR);
        break;

    case tie:
        // render_game_over_state(renderer, game, &TIE_COLOR);
        tictactoe_draw_game_over_state(object, &TIE_COLOR);
        break;
    case quit:
        break;
    
    default: {}

    }
}

static void tictactoe_draw_grid(void *object, const SDL_Color *color)
{
    tictactoe_t *tictactoe = (tictactoe_t *)object;

    SDL_SetRenderDrawColor(tictactoe->renderer, color->r, color->g, color->b, 255);

    for (int i = 1; i < N; ++i)
    {

        SDL_RenderDrawLine(tictactoe->renderer,
                           i * CELL_WIDTH,
                           0,
                           i * CELL_WIDTH,
                           SCREEN_HEIGHT);

        SDL_RenderDrawLine(tictactoe->renderer,
                           0,
                           i * CELL_HEIGHT,
                           SCREEN_WIDTH,
                           i * CELL_HEIGHT);
    }
}

static void tictactoe_draw_x(void *object, int row, int column, const SDL_Color *color)
{
    const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
    const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

    tictactoe_t *tictactoe = (tictactoe_t *)object;

    thickLineRGBA(tictactoe->renderer,
                  center_x - half_box_side,
                  center_y - half_box_side,
                  center_x + half_box_side,
                  center_y + half_box_side,
                  10,
                  color->r,
                  color->g,
                  color->b,
                  255);
                  
    thickLineRGBA(tictactoe->renderer,
                  center_x + half_box_side,
                  center_y - half_box_side,
                  center_x - half_box_side,
                  center_y + half_box_side,
                  10,
                  color->r,
                  color->g,
                  color->b,
                  255);
}

static void tictactoe_draw_o(void *object, int row, int column, const SDL_Color *color)
{
    const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
    const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

    tictactoe_t *tictactoe = (tictactoe_t *)object;

    filledCircleRGBA(tictactoe->renderer,
                     center_x, center_y, half_box_side + 5,
                     color->r, color->g, color->b, 255);
                     
    filledCircleRGBA(tictactoe->renderer,
                     center_x, center_y, half_box_side - 5,
                     0, 0, 0, 255);
}

static void tictactoe_draw_board(void *object, const SDL_Color *player_x_color, const SDL_Color *player_o_color)
{
    tictactoe_t *tictactoe = (tictactoe_t *)object;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            switch (tictactoe->board[i * N + j])
            {
                case player_x:
                    tictactoe_draw_x(tictactoe, i, j, player_x_color);
                    break;

                case player_o:
                    tictactoe_draw_o(tictactoe, i, j, player_o_color);
                    break;

                default: {}

            }
        }
    }
}

static void tictactoe_draw_running_state(void *object, const SDL_Color *color)
{
    tictactoe_draw_grid(object, color);

    tictactoe_draw_board(object,
                         &PLAYER_X_COLOR,
                         &PLAYER_O_COLOR);
}

static void tictactoe_draw_game_over_state(void *object, const SDL_Color *color)
{
    tictactoe_draw_grid(object, color);
    tictactoe_draw_board(object, color, color);
}