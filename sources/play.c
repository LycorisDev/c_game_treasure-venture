#include "../headers/play.h"
#include "../headers/characters.h"
#include "../headers/locations.h"
#include "../headers/input.h"

#include <dlfcn.h>

int execute_twenty_squares(const char* character)
{
    char input[4];
    void* mini_game_obj;
    int (*mini_game_func)();
    int mini_game_result = EXIT_FAILURE;

    char prompt_player_wants_to_play[150] = "\n\t[Do you want to play Twenty Squares with the ";
    strcat(prompt_player_wants_to_play, character);
    get_string_input(input, "yes_no", prompt_player_wants_to_play, "? Yes/No]");
    if (strcmp(input, "no") == 0)
        return EXIT_SUCCESS;

    /* Load the mini-game library (= shared object) */
    mini_game_obj = dlopen("./plugins/libtwenty-squares.so", RTLD_NOW);
    if (!mini_game_obj)
    {
        fprintf(stderr, "Error loading mini-game library: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    /* Obtain a pointer to the mini-game entry point function */
    *(void **) (&mini_game_func) = dlsym(mini_game_obj, "start");
    if (!mini_game_func)
    {
        fprintf(stderr, "Error obtaining pointer to mini-game entry point function: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    /* Call the mini-game function using the function pointer */
    mini_game_result = (*mini_game_func)();

    /* Unload the mini-game library */
    dlclose(mini_game_obj);

    return mini_game_result;
}

void execute_play(void)
{
    int i;
    int exit_twenty_squares = EXIT_FAILURE;

    for (i = 0; i < NBR_CHARACTERS; ++i)
    {
        if (!PLAYER->current_location->characters[i])
        {
            printf("\nYou see no one around you to play with.\n\n");
            break;
        }

        if (PLAYER->current_location->characters[i] == PLAYER)
            continue;

        exit_twenty_squares = execute_twenty_squares(PLAYER->current_location->characters[i]->tags[1]);
        if (exit_twenty_squares == EXIT_FAILURE)
            printf("\n\t[Error: Something went wrong with the mini-game 'Twenty Squares'.]\n");

        LOCATION_NAME
        describe_location(PLAYER->current_location);
        printf("\n\n");
        break;
    }

    return;
}

