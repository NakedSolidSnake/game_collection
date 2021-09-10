#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <game_interface.h>
#include <game_selection.h>
#include <game_loop.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <game name>\n", argv[0]);
        fprintf(stderr, "Usage: %s help - to show the available games\n", argv[0]);
        return EXIT_FAILURE;
    }

    if(strncmp("help", argv[1], 4) == 0)
    {
        //print menu
        printf("spaceship\n");
        printf("breakoutless\n");
        printf("tic tac toe\n");
    }

    else 
    {
        //run the game
        game_base_t *game_selected = game_selection(argv[1]);
        if(game_selected)
        {
            game_loop(game_selected);
        }
    }


    return 0;
}