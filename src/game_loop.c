#include <game_interface.h>

static bool is_interface_valid(game_base_t *game);

bool game_loop(game_base_t *game, void *object)
{
    bool state = false;
    

    if(is_interface_valid(game) == true)
    {

        if(game->init(object) == false)
        {
            // TODO
        }

        while(true)
        {
            if(game->input(object) == false)
                break;

            if(game->collision(object) == false)
                break;
                
            if(game->update(object) == false)
                break;

            if(game->draw(object) == false)
                break;
        }

        state = game->destroy(object);
    }

    return state;
}


static bool is_interface_valid(game_base_t *game)
{
    bool state = false;

    do
    {
        if (!game)
            break;

        else if(!game->init)
            break;

        else if(!game->input)
            break;

        else if(!game->collision)
            break;

        else if(!game->update)
            break;

        else if(!game->draw)
            break;        

        state = true;
        
    } while (false);

    return state;
}