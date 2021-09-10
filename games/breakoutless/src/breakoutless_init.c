#include <breakoutless.h>

typedef bool (*breakoutless_callback)(void *object);

static bool breakoutless_sdl_init(void *object);
static bool breakoutless_window_create(void *object);
static bool breakoutless_render_create(void *object);
static bool breakoutless_image_init(void *object);
static bool breakoutless_load_logo_image(void *object);
static bool breakoutless_load_game_over_image(void *object);
static bool breakoutless_font_init(void *object);
static bool breakoutless_load_press_start_font(void *object);
static bool breakoutless_load_points_font(void *object);
static bool breakoutless_load_speedup_font(void *object);
static bool breakoutless_audio_init(void *object);
static bool breakoutless_load_audio_intro(void *object);
static bool breakoutless_load_sound_wall(void *object);
static bool breakoutless_load_sound_paddle(void *object);
static bool breakoutless_load_sound_ground(void *object);


bool breakoutless_init(void *object)
{    
    bool status = true;

    breakoutless_callback breakoutless_callbacks[] =
    {
        breakoutless_sdl_init,
        breakoutless_window_create,
        breakoutless_render_create,
        breakoutless_image_init,
        breakoutless_load_logo_image,
        breakoutless_load_game_over_image,
        breakoutless_font_init,        
        breakoutless_load_press_start_font,
        breakoutless_load_points_font,
        breakoutless_load_speedup_font,
        breakoutless_audio_init,
        breakoutless_load_audio_intro,
        breakoutless_load_sound_wall,
        breakoutless_load_sound_paddle,
        breakoutless_load_sound_ground
    };

    int callback_amount = sizeof(breakoutless_callbacks) / sizeof(breakoutless_callbacks[0]);

    for(int i = 0; i < callback_amount; i++)
    {
        if(breakoutless_callbacks[i](object) == false)
        {
            status = false;
            break;
        }
    }

    return status;
}


static bool breakoutless_sdl_init(void *object)
{
    (void)object;
    bool status = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL.\n");
        status = false;
    }

    return status;
}

static bool breakoutless_window_create(void *object)
{
    
    breakoutless_t *breakoutless = (breakoutless_t *)object;
    bool status = true;

    breakoutless->window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS);
    if (!breakoutless->window)
    {
        fprintf(stderr, "Error creating SDL Window.\n");
        status = false;
    }

    return status;
}

static bool breakoutless_render_create(void *object)
{
    breakoutless_t *breakoutless = (breakoutless_t *)object;
    bool status = true;

    breakoutless->renderer = SDL_CreateRenderer(breakoutless->window, -1, 0);
    if (!breakoutless->renderer)
    {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        status = false;
    }

    return status;
}

static bool breakoutless_image_init(void *object)
{   
    (void)object;
    bool status = true;
    int image_type = IMG_INIT_PNG;
    int image_ret;

    image_ret = IMG_Init(image_type);
    if (!(image_ret & image_type))
    {
        fprintf(stderr, "Initialize image.\n");
        status = false;
    }

    return status;
}

static bool breakoutless_load_logo_image(void *object)
{
    SDL_Surface *surface_logo = NULL;
    breakoutless_t *breakoutless = (breakoutless_t *)object;
    bool status = false;

    do
    {
        surface_logo = IMG_Load(BREAKOUTLESS_LOGO_PATH);
        if (surface_logo == NULL)
        {
            fprintf(stderr, "Error to create image surface.\n");
            break;
        }

        breakoutless->texture_logo = SDL_CreateTextureFromSurface(breakoutless->renderer, surface_logo);
        if (breakoutless->texture_logo == NULL)
        {
            fprintf(stderr, "Error to create texture from surface.\n");
            break;
        }

        status = true;

    } while(false);

    
    if(surface_logo)
        SDL_FreeSurface(surface_logo);
    
    return status;
}

static bool breakoutless_load_game_over_image(void *object)
{
    bool status = false;
    breakoutless_t * breakoutless = (breakoutless_t *)object;
    SDL_Surface *surface_game_over = NULL;

    do 
    {
        surface_game_over = IMG_Load(BREAKOUTLESS_GAME_OVER_PATH);
        if (surface_game_over == NULL)
        {
            fprintf(stderr, "Error to create image surface.\n");
            break;
        }

        breakoutless->texture_game_over = SDL_CreateTextureFromSurface(breakoutless->renderer, surface_game_over);
        if (breakoutless->texture_game_over == NULL)
        {
            fprintf(stderr, "Error to create texture from surface.\n");
            break;
        }

        status = true;

    } while(false);

    
    if(surface_game_over)
        SDL_FreeSurface(surface_game_over);

    return status;
}

static bool breakoutless_font_init(void *object)
{
    bool status = true;
    (void)object;

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Error to initialize fonts.\n");
        status = false;
    }

    return status;
}

static bool breakoutless_load_press_start_font(void *object)
{
    bool status = true;
    breakoutless_t * breakoutless = (breakoutless_t *)object;

    breakoutless->font = TTF_OpenFont(BREAKOUTLESS_FONT_PATH, 48);
    if (breakoutless->font == NULL)
    {
        fprintf(stderr, "Error to open font.\n");
        status = false;
    }

    return status;
}

static bool breakoutless_load_points_font(void *object)
{
    bool status = true;
    breakoutless_t * breakoutless = (breakoutless_t *)object;

    breakoutless->points_font = TTF_OpenFont(BREAKOUTLESS_FONT_PATH, 18);
    if (breakoutless->font == NULL)
    {
        fprintf(stderr, "Error to open font.\n");
        return false;
    }
    return status;
}

static bool breakoutless_load_speedup_font(void *object)
{
    bool status = true;
    breakoutless_t * breakoutless = (breakoutless_t *)object;

    breakoutless->speedup_font = TTF_OpenFont(BREAKOUTLESS_FONT_PATH, 48);

    if (breakoutless->speedup_font == NULL)
    {
        fprintf(stderr, "Error to open font.\n");
        status = false;
    }

    return status;
}

static bool breakoutless_audio_init(void *object)
{
    bool status = true;
    (void)object;

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        status = false;
    }

    return status;
}

static bool breakoutless_load_audio_intro(void *object)
{
    bool status = true;
    breakoutless_t * breakoutless = (breakoutless_t *)object;

    breakoutless->music_intro = Mix_LoadMUS( BREAKOUTLESS_INTRO_MUSIC );
    if( breakoutless->music_intro == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        status = false;
    }

    return status;
}

static bool breakoutless_load_sound_wall(void *object)
{
    bool status = true;
    breakoutless_t * breakoutless = (breakoutless_t *)object;

    breakoutless->sound_wall = Mix_LoadWAV( BREAKOUTLESS_WALL_SOUND );
    if( breakoutless->sound_wall == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        status = false;
    }

    return status;
}

static bool breakoutless_load_sound_paddle(void *object)
{
    bool status = true;
    breakoutless_t * breakoutless = (breakoutless_t *)object;

    breakoutless->sound_paddle = Mix_LoadWAV( BREAKOUTLESS_PADDLE_SOUND );
    if( breakoutless->sound_paddle == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        status = false;
    }

    return status;
}

static bool breakoutless_load_sound_ground(void *object)
{
    bool status = true;
    breakoutless_t * breakoutless = (breakoutless_t *)object;

    breakoutless->sound_ground = Mix_LoadWAV( BREAKOUTLESS_GROUND_SOUND);
    if( breakoutless->sound_ground == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        status = false;
    }

    return status;
}