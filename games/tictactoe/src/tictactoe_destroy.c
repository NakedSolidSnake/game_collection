#include <ticktactoe.h>
#include <stdio.h>

bool tictactoe_destroy(void *object)
{
    bool status = true;
    tictactoe_t *tictactoe = (tictactoe_t *)object;
    (void)tictactoe;

    printf("%s\n", __FUNCTION__);

    SDL_DestroyRenderer(tictactoe->renderer);
    SDL_DestroyWindow(tictactoe->window);
    SDL_Quit();

    return status;
}