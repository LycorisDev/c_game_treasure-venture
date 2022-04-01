#include "../headers/characters.h"
#include "../headers/play.h"
#include "../twenty_squares/headers/twenty_squares_main.h"

void execute_play(void)
{
    int id_character = PLAYER->current_location->list_of_characters_by_id[0];
    int exit_twenty_squares = EXIT_FAILURE;

    if (id_character == ID_ITEM_NONE)
    {
        printf("\nYou see no one around you to play with.\n\n");
    }
    else
    {
        exit_twenty_squares = execute_twenty_squares(retrieve_default_character_tag_by_id(id_character));
        if (exit_twenty_squares == EXIT_FAILURE)
            printf("\n\t[Error: Something went wrong with the mini-game 'Twenty Squares'.]\n\n");
        printf("%s\n\n", PLAYER->current_location->description);
    }
    return;
}

