#include <ticktactoe.h>
#include <stdio.h>

static void tictactoe_input_switch_player(void *object);
static void tictactoe_input_player_turn(void *object, int row, int column);

bool tictactoe_update(void *object)
{
    bool status = true;
    tictactoe_t *tictactoe = (tictactoe_t *)object;
    (void)tictactoe;


    if(tictactoe->clicked)
    {
        tictactoe_input_player_turn(object, tictactoe->row, tictactoe->column);
        // tictactoe_input_switch_player(object);
    }
    
    return status;
}

static void tictactoe_input_switch_player(void *object)
{
    tictactoe_t *tictactoe = (tictactoe_t *)object;

    if (tictactoe->player == player_x)
    {
        tictactoe->player = player_o;
    }
    else if (tictactoe->player == player_o)
    {
        tictactoe->player = player_x;
    }
}

static void tictactoe_input_player_turn(void *object, int row, int column)
{
    tictactoe_t *tictactoe = (tictactoe_t *)object;

    if (tictactoe->board[row * N + column] == empty)
    {
        tictactoe->board[row * N + column] = tictactoe->player;
        tictactoe_input_switch_player(object);
        // game_over_condition(game);
    }
}