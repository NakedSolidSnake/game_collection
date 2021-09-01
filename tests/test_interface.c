#include <game_interface.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_CALLING_INIT       "Calling test init"
#define TEST_CALLING_INPUT      "Calling test input"
#define TEST_CALLING_UPDATE     "Calling test update"
#define TEST_CALLING_COLLISION  "Calling test collision"
#define TEST_CALLING_DRAW       "Calling test draw"

static bool test_init(void *object);
static bool test_input(void *object);
static bool test_update(void *object);
static bool test_collision(void *object);
static bool test_draw(void *object);

int main()
{
    bool status = false;
    game_base_t test_game =
    {
        .init = test_init, 
        .input = test_input,
        .collision = test_collision,
        .update = test_update,
        .draw = test_draw
    };

    if( game_loop(&test_game, NULL) == true)
        status = true;

    return status == false ? EXIT_SUCCESS : EXIT_FAILURE;
}


static bool test_init(void *object)
{
    printf("%s\n", TEST_CALLING_INIT);
    return true;
}

static bool test_input(void *object)
{
    printf("%s\n", TEST_CALLING_INPUT);
    return true;
}

static bool test_update(void *object)
{
    printf("%s\n", TEST_CALLING_UPDATE);
    return true;
}

static bool test_collision(void *object)
{
    printf("%s\n", TEST_CALLING_COLLISION);
    return true;
}

static bool test_draw(void *object)
{
    printf("%s\n", TEST_CALLING_DRAW);
    return false;
}