#include "../headers/look.h"
#include "../headers/main.h"
#include "../headers/commands.h"
#include "../headers/items.h"
#include "../headers/characters.h"
#include "../headers/locations.h"
#include "../headers/events.h"
#include "../headers/character.h"

static int bool_no_item_at_current_location(void);
/* static int bool_no_character_at_current_location(void); */
static int bool_player_is_the_only_character_at_current_location(void);

void execute_look(void)
{
    int i;
    Item** items_with_same_tag = NULL;
    Character** characters_with_same_tag = NULL;

    if (!strcmp(command.object, "around"))
    {
        describe_location(PLAYER->current_location);
    }
    else if (bool_no_item_at_current_location() && bool_player_is_the_only_character_at_current_location())
    {
        add_output("\t[Try 'look around'.]\n\n");
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
                        add_output("%s\n\n", characters_with_same_tag[0]->description);
                    }
                }
                else
                {
                    add_output("There is more than one character in your vicinity for which this tag works.\n");
                    memset(command.object, 0, sizeof(command.object));
                }
            }
            else if (!items_with_same_tag[1])
            {
                add_output("%s\n\n", items_with_same_tag[0]->description_detailed);
                event_player_finds_entry_doors_key(items_with_same_tag[0]->id);
            }
            else if (!characters_with_same_tag || !characters_with_same_tag[0])
            {
                add_output("There is more than one item in your vicinity for which this tag works.\n");
                memset(command.object, 0, sizeof(command.object));
            }
            else
            {
                add_output("There is more than one item and character in your vicinity for which this tag works.\n");
                memset(command.object, 0, sizeof(command.object));
            }
        }

        if (!*command.object)
        {
            add_output("\t[Try:]\n");
            add_output("\t\t['Look around'.]\n");
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                if (PLAYER->current_location->items[i] == 0)
                    break;
                add_output("\t\t['Look %s'.]\n", PLAYER->current_location->items[i]->tags[0]);
            }
            for (i = 0; i < NBR_CHARACTERS; ++i)
            {
                if (!PLAYER->current_location->characters[i])
                    break;
                if (PLAYER->current_location->characters[i] == PLAYER)
                    continue;
                add_output("\t\t['Look %s'.]\n", PLAYER->current_location->characters[i]->tags[0]);
            }
            add_output("\n");
        }
    }

    free(items_with_same_tag);
    free(characters_with_same_tag);
    return;
}

static int bool_no_item_at_current_location(void)
{
    return !PLAYER->current_location->items[0];
}

/*
static int bool_no_character_at_current_location(void)
{
    return !PLAYER->current_location->characters[0];
}
*/

static int bool_player_is_the_only_character_at_current_location(void)
{
    return PLAYER->current_location->characters[0] == PLAYER && !PLAYER->current_location->characters[1];
}

