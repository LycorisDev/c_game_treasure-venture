#include "../headers/play.h"
#include "../twenty_squares/headers/twenty_squares_main.h"

void execute_play(void)
{
    int exit_twenty_squares = EXIT_FAILURE;

    if (PLAYER->current_location->list_of_characters_by_id[0] == ID_ITEM_NONE)
    {
        printf("\nYou see no one around you to play with.\n\n");
    }
    else
    {
        exit_twenty_squares = execute_twenty_squares();
        if (exit_twenty_squares == EXIT_FAILURE)
            printf("\n\t[Error: Something went wrong with the mini-game 'Twenty Squares'.]\n\n");
        printf("%s\n", PLAYER->current_location->description);
    }
    return;
}

