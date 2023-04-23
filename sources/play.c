#include "../headers/play.h"
#include "../headers/parser.h"
#include "../headers/characters.h"
#include "../headers/locations.h"

static void static_mini_game(const int yes_no);
/* static void dynamic_mini_game(int yes_no); */

void execute_play(void)
{
    int i;

    for (i = 0; i < NBR_CHARACTERS; ++i)
    {
        if (!PLAYER->current_location->characters[i])
        {
            add_output("You see no one around you to play with.\n\n");
            return;
        }

        if (PLAYER->current_location->characters[i] == PLAYER)
            continue;

        break;
    }

    add_output("\t[Do you want to play Twenty Squares with the %s? Yes/No]\n\n", PLAYER->current_location->characters[i]->tags[1]);
    yes_no_callback = &static_mini_game;
    return;
}

static void static_mini_game(const int yes_no)
{
    if (yes_no)
        start_twenty_squares();

    describe_location(PLAYER->current_location);
    return;
}

/*
static void dynamic_mini_game(int yes_no)
{
    LIB_HANDLE mini_game_obj = NULL;
    int (*mini_game_func)() = NULL;

    if (yes_no)
    {
        mini_game_obj = LOAD_LIB(LIB_PATH_TWENTY_SQUARES);
        if (!mini_game_obj)
        {
            add_output("\t[Error: The Twenty Squares library can't be loaded -> %s]\n", LIB_ERROR);
            return;
        }

        #ifdef _WIN32
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wpedantic"
        #endif
        *(void **) (&mini_game_func) = LIB_FUNC(mini_game_obj, "start_twenty_squares");
        #ifdef _WIN32
        #pragma GCC diagnostic pop
        #endif
        if (!mini_game_func)
        {
            add_output("\t[Error: The pointer to the Twenty Squares library start function can't be obtained -> %s]\n", LIB_ERROR);
            UNLOAD_LIB(mini_game_obj);
            return;
        }

        (*mini_game_func)();

        UNLOAD_LIB(mini_game_obj);
    }

    describe_location(PLAYER->current_location);
    return;
}
*/

