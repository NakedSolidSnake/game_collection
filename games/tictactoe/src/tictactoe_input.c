#include <ticktactoe.h>
#include <stdio.h>


bool tictactoe_input(void *object)
{
    bool status = true;
    tictactoe_t *tictactoe = (tictactoe_t *)object;
    (void)tictactoe;

    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            tictactoe->state = quit;
            status = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if(tictactoe->state != running && tictactoe->state != quit)
            {
                tictactoe->state = restart;
            }
            else 
            {
                tictactoe->row = e.button.y / CELL_HEIGHT;
                tictactoe->column = e.button.x / CELL_WIDTH;
                tictactoe->clicked = true;
            }
            break; 

        default:{}    
        }

        if(tictactoe->state != running && tictactoe->state != quit)
            continue;
    }

    return status;
}

