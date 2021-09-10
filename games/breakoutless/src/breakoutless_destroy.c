#include <breakoutless.h>

bool breakoutless_destroy(void *object)
{
    breakoutless_t * breakoutless = (breakoutless_t *)object;

    if(breakoutless->texture_label != NULL)
        SDL_DestroyTexture(breakoutless->texture_label);
    TTF_CloseFont(breakoutless->font);

    if(breakoutless->texture_speedup != NULL)
        SDL_DestroyTexture(breakoutless->texture_speedup);

    TTF_CloseFont(breakoutless->speedup_font);

    TTF_CloseFont(breakoutless->points_font);

    Mix_FreeMusic(breakoutless->music_intro);

    SDL_DestroyTexture(breakoutless->texture_speedup);
    SDL_DestroyTexture(breakoutless->texture_logo);
    SDL_DestroyTexture(breakoutless->texture_game_over);

    SDL_DestroyRenderer(breakoutless->renderer);
    SDL_DestroyWindow(breakoutless->window);

    TTF_Quit();
    SDL_Quit();

    return true;   
}
