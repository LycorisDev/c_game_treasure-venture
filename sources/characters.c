#include "../headers/characters.h"
#include "../headers/main.h"

/* Declared as extern in ../headers/game.h, included in ../headers/characters.h */
Character list_characters[NBR_CHARACTERS];

static int bool_character_matches_parser(const Character* character, const char* parser);

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

void display_character_suggestions(Character** character_collection, const char* command)
{
    int i;

    if (!character_collection[0] || character_collection[0] == PLAYER)
        return;

    add_output("\t[Try:]\n");

    for (i = 0; i < NBR_CHARACTERS; ++i)
    {
        if (!character_collection[i])
            break;
        if (character_collection[i] == PLAYER)
            continue;
        add_output("\t\t['%s %s'.]\n", command, character_collection[i]->tags[0]);
    }
    add_output("\n");
    return;
}

Character** retrieve_characters(Character** character_collection, const char* parser)
{
    int i, j;
    Character** characters_with_same_tag = calloc(NBR_CHARACTERS, sizeof(Character*));
    if (!characters_with_same_tag)
        return NULL;

    for (i = 0, j = 0; i < NBR_CHARACTERS; ++i)
    {
        if (!character_collection[i])
            break;

        if (!parser || bool_character_matches_parser(character_collection[i], parser))
            characters_with_same_tag[j++] = character_collection[i];
    }

    return characters_with_same_tag;
}

static int bool_character_matches_parser(const Character* character, const char* parser)
{
    int i;
    for (i = 0; i < NBR_TAGS; ++i)
    {
        if (!character->tags[i])
            return 0;

        if (!strcmp(parser, character->tags[i]))
            return 1;
    }
    return 0;
}

