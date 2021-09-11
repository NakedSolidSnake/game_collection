#include <game_selection.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>


typedef struct 
{
    const char *game_name;
    const char *game_lib_name;
} game_list;

static game_list games[] = 
{
    {.game_name = "spaceship", .game_lib_name = "none"},
    {.game_name = "breakoutless", .game_lib_name = "../lib/libbreakoutless.so"},
    {.game_name = "tictactoe", .game_lib_name = "../lib/libtictactoe.so"},
};

static int game_amount = sizeof(games) / sizeof(games[0]);

game_base_t *game_selection(const char *game_name)
{
    game_base_t *game_base = NULL;
    void *handle;

    for(int i = 0; i < game_amount; i++)
    {
        if(strncmp(game_name, games[i].game_name, strlen(games[i].game_name)) == 0)
        {
            //load dynamically
            printf("game: %s selected\n", game_name);
            handle = dlopen(games[i].game_lib_name, RTLD_LAZY);
            if(handle)
            {
                game_plugin plugin = dlsym(handle, "game_builder");
                game_base = plugin();
            }
            break;
        }
    }

    return game_base;
}