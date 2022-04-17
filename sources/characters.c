#include "../headers/characters.h"

/* Declared as extern in ../headers/game.h, included in ../headers/characters.h */
Character list_characters[NBR_CHARACTERS];

void populate_list_characters(void)
{
    memset(list_characters, 0, NBR_CHARACTERS * sizeof(Character));

    PLAYER->id = ID_CHARACTER_PLAYER;
    memcpy(PLAYER->name, "player", LENGTH_NAME);
    memcpy(PLAYER->tags[0], "player / self / me / myself", LENGTH_NAME);
    memcpy(PLAYER->tags[1], "player", LENGTH_NAME);
    memcpy(PLAYER->tags[2], "self", LENGTH_NAME);
    memcpy(PLAYER->tags[3], "me", LENGTH_NAME);
    memcpy(PLAYER->tags[4], "myself", LENGTH_NAME);
    memcpy(PLAYER->description, "NO_DESCRIPTION.", LENGTH_DESCRIPTION);
    PLAYER->current_location = LOCATION_OUTSIDE;

    CHARACTER_LIBRARIAN->id = ID_CHARACTER_LIBRARIAN;
    memcpy(CHARACTER_LIBRARIAN->name, "librarian", LENGTH_NAME);
    memcpy(CHARACTER_LIBRARIAN->tags[0], "librarian / mansion librarian", LENGTH_NAME);
    memcpy(CHARACTER_LIBRARIAN->tags[1], "librarian", LENGTH_NAME);
    memcpy(CHARACTER_LIBRARIAN->tags[2], "mansion librarian", LENGTH_NAME);
    memcpy(CHARACTER_LIBRARIAN->description, "The librarian seems friendly.", LENGTH_DESCRIPTION);
    CHARACTER_LIBRARIAN->current_location = LOCATION_OLD_LIBRARY;
    return;
}

Character** retrieve_characters_by_parser_from_current_location(const char* parser)
{
    int i, j, k;
    Character** characters_with_same_tag = calloc(NBR_CHARACTERS, sizeof(Character*));
    if (!characters_with_same_tag)
        return NULL;

    for (i = 0, k = 0; i < NBR_CHARACTERS; ++i)
    {
        if (!PLAYER->current_location->characters[i])
            break;

        for (j = 1; j < NBR_TAGS; ++j)
        {
            if (!PLAYER->current_location->characters[i]->tags[j])
                break;

            if (!strcmp(parser, PLAYER->current_location->characters[i]->tags[j]))
            {
                characters_with_same_tag[k++] = PLAYER->current_location->characters[i];
                break;
            }
        }
    }

    return characters_with_same_tag;
}

