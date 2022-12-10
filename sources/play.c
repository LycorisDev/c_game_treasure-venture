#include "../headers/play.h"
#include "../headers/characters.h"
#include "../headers/locations.h"
#include "../twenty_squares/headers/twenty_squares_main.h"

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

