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
    Item** items_with_same_tag = NULL;
    Character** characters_with_same_tag = NULL;

    if (!strcmp(command.object, "around"))
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
        if (*command.object)
        {
            items_with_same_tag = retrieve_items_by_parser_from_current_location(command.object);
            characters_with_same_tag = retrieve_characters_by_parser_from_current_location(command.object);

            if (!items_with_same_tag || !items_with_same_tag[0])
            {
                if (!characters_with_same_tag || !characters_with_same_tag[0])
                    memset(command.object, 0, sizeof(command.object));
                else if (!characters_with_same_tag[1])
                {
                    if (characters_with_same_tag[0] == PLAYER)
                    {
                        /* 'look [player]' is the same as the 'character' command */
                        execute_character();
                    }
                    else
                    {
                        printf("\n%s\n\n", characters_with_same_tag[0]->description);
                    }
                }
                else
                {
                    printf("\nThere is more than one character in your vicinity for which this tag works.\n");
                    memset(command.object, 0, sizeof(command.object));
                }
            }
            else if (!items_with_same_tag[1])
            {
                printf("\n%s\n\n", items_with_same_tag[0]->description_detailed);
                EVENT_PLAYER_FINDS_ENTRY_DOORS_KEY((items_with_same_tag + 0))
            }
            else if (!characters_with_same_tag || !characters_with_same_tag[0])
            {
                printf("\nThere is more than one item in your vicinity for which this tag works.\n");
                memset(command.object, 0, sizeof(command.object));
            }
            else
            {
                printf("\nThere is more than one item and character in your vicinity for which this tag works.\n");
                memset(command.object, 0, sizeof(command.object));
            }
        }

        if (!*command.object)
        {
            printf("\n\t[Try:]\n");
            printf("\t\t['Look around'.]\n");
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                if (PLAYER->current_location->items[i] == 0)
                    break;
                printf("\t\t['Look %s'.]\n", PLAYER->current_location->items[i]->tags[0]);
            }
            for (i = 0; i < NBR_CHARACTERS; ++i)
            {
                if (!PLAYER->current_location->characters[i])
                    break;
                if (PLAYER->current_location->characters[i] == PLAYER)
                    continue;
                printf("\t\t['Look %s'.]\n", PLAYER->current_location->characters[i]->tags[0]);
            }
            printf("\n");
        }
    }

    free(items_with_same_tag);
    free(characters_with_same_tag);
    return;
}

