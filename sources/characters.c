#include "../headers/characters.h"

/* Declared as extern in ../headers/game.h, included in ../headers/characters.h */
Character list_characters[NBR_CHARACTERS];

void populate_list_characters(void)
{
    CHARACTER_NONE->id = ID_CHARACTER_NONE;
    memcpy(CHARACTER_NONE->tags[0], "NO_TAG", LENGTH_NAME);
    memcpy(CHARACTER_NONE->tags[1], "NO_TAG", LENGTH_NAME);
    memcpy(CHARACTER_NONE->description, "NO_DESCRIPTION.", LENGTH_DESCRIPTION);
    CHARACTER_NONE->previous_location = LOCATION_NONE;
    CHARACTER_NONE->current_location = LOCATION_NONE;
    CHARACTER_NONE->inventory[0] = ID_ITEM_NONE;

    PLAYER->id = ID_CHARACTER_PLAYER;
    memcpy(PLAYER->name, "player", LENGTH_NAME);
    memcpy(PLAYER->tags[0], "player / me / myself", LENGTH_NAME);
    memcpy(PLAYER->tags[1], "player", LENGTH_NAME);
    memcpy(PLAYER->tags[2], "me", LENGTH_NAME);
    memcpy(PLAYER->tags[3], "myself", LENGTH_NAME);
    memcpy(PLAYER->description, "NO_DESCRIPTION.", LENGTH_DESCRIPTION);
    PLAYER->previous_location = LOCATION_NONE;
    PLAYER->current_location = LOCATION_OUTSIDE;
    PLAYER->inventory[0] = ID_ITEM_NONE;

    CHARACTER_LIBRARIAN->id = ID_CHARACTER_LIBRARIAN;
    memcpy(CHARACTER_LIBRARIAN->name, "librarian", LENGTH_NAME);
    memcpy(CHARACTER_LIBRARIAN->tags[0], "librarian / mansion librarian", LENGTH_NAME);
    memcpy(CHARACTER_LIBRARIAN->tags[1], "librarian", LENGTH_NAME);
    memcpy(CHARACTER_LIBRARIAN->tags[2], "mansion librarian", LENGTH_NAME);
    memcpy(CHARACTER_LIBRARIAN->description, "The librarian seems friendly.", LENGTH_DESCRIPTION);
    CHARACTER_LIBRARIAN->previous_location = LOCATION_NONE;
    CHARACTER_LIBRARIAN->current_location = LOCATION_OLD_LIBRARY;
    CHARACTER_LIBRARIAN->inventory[0] = ID_ITEM_NONE;
    return;
}

SameTag* retrieve_character_id_by_parser_from_current_location(const char* parser)
{
    int i, j, k;
    SameTag* characters_with_same_tag = calloc(NBR_CHARACTERS, sizeof(SameTag));
    if (!characters_with_same_tag)
        return NULL;

    for (i = 0, k = 0; i <= NBR_CHARACTERS; ++i)
    {
        if (i == NBR_CHARACTERS || PLAYER->current_location->list_of_characters_by_id[i] == ID_CHARACTER_NONE)
            break;

        for (j = 1; j <= NBR_TAGS; ++j)
        {
            if (j == NBR_TAGS || strcmp("", list_characters[PLAYER->current_location->list_of_characters_by_id[i]].tags[j]) == 0)
                break;

            if (strcmp(parser, list_characters[PLAYER->current_location->list_of_characters_by_id[i]].tags[j]) == 0)
            {
                characters_with_same_tag[k].index = i;
                characters_with_same_tag[k++].id = PLAYER->current_location->list_of_characters_by_id[i];
                break;
            }
        }
    }

    return characters_with_same_tag;
}

