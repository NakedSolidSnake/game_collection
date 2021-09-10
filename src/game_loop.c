#include <game_interface.h>

static bool is_interface_valid(game_base_t *game_interface);

bool game_loop(game_base_t *game_interface)
{
    bool state = false;
    

    if(is_interface_valid(game_interface) == true)
    {

        if(game_interface->init(game_interface->game_object) == false)
        {
            // TODO
        }

        while(true)
        {
            if(game_interface->input(game_interface->game_object) == false)
                break;

            if(game_interface->update(game_interface->game_object) == false)
                break;

            if(game_interface->collision(game_interface->game_object) == false)
                break;
            
            if(game_interface->draw(game_interface->game_object) == false)
                break;
        }

        state = game_interface->destroy(game_interface->game_object);
    }

    return state;
}


static bool is_interface_valid(game_base_t *game_interface)
{
    bool state = false;

    do
    {
        if (!game_interface)
            break;

        else if(!game_interface->game_object)
            break;

        else if(!game_interface->init)
            break;

        else if(!game_interface->input)
            break;

        else if(!game_interface->collision)
            break;

        else if(!game_interface->update)
            break;

        else if(!game_interface->draw)
            break; 

        else if(!game_interface->destroy)       
            break;

        state = true;
        
    } while (false);

    return state;
}