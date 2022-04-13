#include "../headers/look.h"
#include "../headers/commands.h"
#include "../headers/items.h"
#include "../headers/characters.h"
#include "../headers/locations.h"
#include "../headers/events.h"
#include "../headers/character.h"

void execute_look(void)
{
    int i;
    SameTag* items_with_same_tag = NULL;
    SameTag* characters_with_same_tag = NULL;

    if (strcmp(command.object, "around") == 0)
    {
        LOCATION_NAME
        describe_location(PLAYER->current_location);
        printf("\n\n");
    }
    else if (NO_ITEM_AT_CURRENT_LOCATION && PLAYER_IS_ONLY_CHARACTER_AT_CURRENT_LOCATION)
    {
        printf("\n\t[Try 'look around'.]\n\n");
    }
    else
    {
        if (strcmp(command.object, "") != 0)
        {
            items_with_same_tag = retrieve_item_id_by_parser_from_current_location(command.object);
            characters_with_same_tag = retrieve_character_id_by_parser_from_current_location(command.object);

            if (!items_with_same_tag || items_with_same_tag[0].id == ID_ITEM_NONE)
            {
                if (!characters_with_same_tag || characters_with_same_tag[0].id == ID_CHARACTER_NONE)
                    memcpy(command.object, "", BIG_LENGTH_WORD);
                else if (characters_with_same_tag[1].id == ID_CHARACTER_NONE)
                {
                    if (characters_with_same_tag[0].id == ID_CHARACTER_PLAYER)
                    {
                        /* 'look player/me/myself' is the same as the 'character' command */
                        execute_character();
                    }
                    else
                    {
                        printf("\n%s\n\n", list_characters[characters_with_same_tag[0].id].description);
                    }
                }
                else
                {
                    printf("\nThere is more than one character in your vicinity for which this tag works.\n");
                    memcpy(command.object, "", BIG_LENGTH_WORD);
                }
            }
            else if (items_with_same_tag[1].id == ID_ITEM_NONE)
            {
                printf("\n%s\n\n", list_items[items_with_same_tag[0].id].description_detailed);
                EVENT_PLAYER_FINDS_ENTRY_DOORS_KEY(items_with_same_tag[0].id)
            }
            else if (!characters_with_same_tag || characters_with_same_tag[0].id == ID_CHARACTER_NONE)
            {
                printf("\nThere is more than one item in your vicinity for which this tag works.\n");
                memcpy(command.object, "", BIG_LENGTH_WORD);
            }
            else
            {
                printf("\nThere is more than one item and character in your vicinity for which this tag works.\n");
                memcpy(command.object, "", BIG_LENGTH_WORD);
            }
        }

        if (strcmp(command.object, "") == 0)
        {
            printf("\n\t[Try:]\n");
            printf("\t\t['Look around'.]\n");
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                if (PLAYER->current_location->list_of_items_by_id[i] == 0)
                    break;
                printf("\t\t['Look %s'.]\n", list_items[PLAYER->current_location->list_of_items_by_id[i]].tags[0]);
            }
            for (i = 0; i < NBR_CHARACTERS; ++i)
            {
                if (PLAYER->current_location->list_of_characters_by_id[i] == ID_CHARACTER_NONE)
                    break;
                if (PLAYER->current_location->list_of_characters_by_id[i] == ID_CHARACTER_PLAYER)
                    continue;
                printf("\t\t['Look %s'.]\n", list_characters[PLAYER->current_location->list_of_characters_by_id[i]].tags[0]);
            }
            printf("\n");
        }
    }

    free(items_with_same_tag);
    free(characters_with_same_tag);
    return;
}

