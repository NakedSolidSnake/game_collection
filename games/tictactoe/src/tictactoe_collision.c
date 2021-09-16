#include <ticktactoe.h>
#include <stdio.h>

static void tictactoe_collision_reset_game(void *object);
static void tictactoe_collision_game_over_condition(void *object);
static int tictactoe_collision_count_cells(const int *board, int cell);
static int tictactoe_collision_check_player_won(void *object, int player);

bool tictactoe_collision(void *object)
{
    bool status = true;
    tictactoe_t *tictactoe = (tictactoe_t *)object;
    (void)tictactoe;

    printf("%s\n", __FUNCTION__);
    if ((tictactoe->clicked && tictactoe->state == running))
    {
        /* code */
        tictactoe_collision_game_over_condition(object);
        tictactoe->clicked = false;
    }
    

    return status;
}

static void tictactoe_collision_reset_game(void *object)
{
    tictactoe_t *tictactoe = (tictactoe_t *)object;

    tictactoe->player = player_x;
    tictactoe->state = running;

    for (int i = 0; i < N * N; ++i)
    {
        tictactoe->board[i] = empty;
    }
}

static void tictactoe_collision_game_over_condition(void *object)
{
    tictactoe_t *tictactoe = (tictactoe_t *)object;

    if (tictactoe_collision_check_player_won(object, player_x))
    {
        tictactoe->state = player_x_won;
    }
    else if (tictactoe_collision_check_player_won(object, player_o))
    {
        tictactoe->state = player_o_won;
    }
    else if (tictactoe_collision_count_cells(tictactoe->board, empty) == 0)
    {
        tictactoe->state = tie;
    }
}

static int tictactoe_collision_count_cells(const int *board, int cell)
{
    int count = 0;

    for (int i = 0; i < N * N; ++i)
    {
        if (board[i] == cell)
        {
            count++;
        }
    }

    return count;
}

static int tictactoe_collision_check_player_won(void *object, int player)
{
    int row_count = 0;
    int column_count = 0;
    int diag1_count = 0;
    int diag2_count = 0;

    tictactoe_t *tictactoe = (tictactoe_t *)object;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (tictactoe->board[i * N + j] == player)
            {
                row_count++;
            }

            if (tictactoe->board[j * N + i] == player)
            {
                column_count++;
            }
        }

        if (row_count >= N || column_count >= N)
        {
            return 1;
        }

        row_count = 0;
        column_count = 0;

        if (tictactoe->board[i * N + i] == player)
        {
            diag1_count++;
        }

        if (tictactoe->board[i * N + N - i - 1] == player)
        {
            diag2_count++;
        }
    }

    return diag1_count >= N || diag2_count >= N;
}