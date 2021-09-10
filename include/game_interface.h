#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <stdbool.h>

typedef struct 
{
    void *game_object;

    bool (*init)(void *object);
    bool (*input)(void *object);
    bool (*update)(void *object);
    bool (*collision)(void *object);
    bool (*draw)(void *object);    
    bool (*destroy)(void *object); 
} game_base_t;

typedef game_base_t *(*game_plugin)(void);

#endif /* GAME_INTERFACE_H */
