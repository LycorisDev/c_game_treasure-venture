#include "../headers/characters.h"

/* Declared as extern in ../headers/game.h, included in ../headers/characters.h */
Character list_characters[NBR_CHARACTERS];

void populate_list_characters(void)
{
    CHARACTER_NONE->character_id = ID_CHARACTER_NONE;
    memcpy(CHARACTER_NONE->description, "NO_DESCRIPTION", LENGTH_DESCRIPTION);
    CHARACTER_NONE->current_location = LOCATION_NONE;
    CHARACTER_NONE->list_of_items_by_id[0] = ID_ITEM_NONE;

    PLAYER->character_id = ID_CHARACTER_PLAYER;
    memcpy(PLAYER->description, "NO_DESCRIPTION", LENGTH_DESCRIPTION);
    PLAYER->current_location = LOCATION_OUTSIDE;
    PLAYER->list_of_items_by_id[0] = ID_ITEM_NONE;

    CHARACTER_LIBRARIAN->character_id = ID_CHARACTER_LIBRARIAN;
    memcpy(CHARACTER_LIBRARIAN->description, "The librarian seems friendly.", LENGTH_DESCRIPTION);
    CHARACTER_LIBRARIAN->current_location = LOCATION_OLD_LIBRARY;
    CHARACTER_LIBRARIAN->list_of_items_by_id[0] = ID_ITEM_NONE;
    return;
}

char* retrieve_default_character_tag_by_id(const int character_id)
{
    switch (character_id)
    {
        case ID_CHARACTER_PLAYER:
            return "player";
        case ID_CHARACTER_LIBRARIAN:
            return "librarian";
        default:
            return "";
    }
}

int retrieve_character_id_by_parser(const char* parser)
{
    if (strcmp(parser, "player") == 0)
        return ID_CHARACTER_PLAYER;
    else if (strcmp(parser, "librarian") == 0)
        return ID_CHARACTER_LIBRARIAN;
    else
        return ID_CHARACTER_NONE;
}

int bool_parser_and_character_id_do_match(const char* parser, const int character_id)
{
    switch(character_id)
    {
        case ID_CHARACTER_PLAYER:
            return strcmp(parser, "player") == 0 ? 1 : 0;
        case ID_CHARACTER_LIBRARIAN:
            return strcmp(parser, "librarian") == 0 ? 1 : 0;
        default:
            return 0;
    }
}

