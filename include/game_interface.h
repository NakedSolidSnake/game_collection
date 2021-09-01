#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <stdbool.h>

typedef struct 
{
    bool (*init)(void *object);
    bool (*input)(void *object);
    bool (*update)(void *object);
    bool (*collision)(void *object);
    bool (*draw)(void *object);    
    bool (*destroy)(void *object); 
} game_base_t;


bool game_loop(game_base_t *game, void *object);

#endif /* GAME_INTERFACE_H */
