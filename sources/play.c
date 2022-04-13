#include "../headers/characters.h"
#include "../headers/play.h"
#include "../twenty_squares/headers/twenty_squares_main.h"

void execute_play(void)
{
    int i;
    int exit_twenty_squares = EXIT_FAILURE;

    for (i = 0; i < NBR_CHARACTERS; ++i)
    {
        if (PLAYER->current_location->list_of_characters_by_id[i] == ID_CHARACTER_PLAYER 
            || PLAYER->current_location->list_of_characters_by_id[i] == ID_CHARACTER_NONE)
        {
            printf("\nYou see no one around you to play with.\n\n");
            break;
        }
        else
        {
            exit_twenty_squares = execute_twenty_squares(list_characters[PLAYER->current_location->list_of_characters_by_id[i]].tags[1]);
            if (exit_twenty_squares == EXIT_FAILURE)
                printf("\n\t[Error: Something went wrong with the mini-game 'Twenty Squares'.]\n\n");
            printf("%s\n\n", PLAYER->current_location->description);
            break;
        }
    }
    return;
}

