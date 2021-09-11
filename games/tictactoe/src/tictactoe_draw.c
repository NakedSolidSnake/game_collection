#include <ticktactoe.h>
#include <stdio.h>

bool tictactoe_draw(void *object)
{
    bool status = true;
    tictactoe_t *tictactoe = (tictactoe_t *)object;
    (void)tictactoe;

    printf("%s\n", __FUNCTION__);

    return status;
}