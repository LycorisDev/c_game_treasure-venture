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
    Item** items_with_same_tag = NULL;
    Character** characters_with_same_tag = NULL;
    int bool_item_match = 0, bool_character_match = 0;
    int bool_several_item_matches = 0, bool_several_character_matches = 0;

    if (!strcmp(command.object, "around"))
    {
        describe_location(PLAYER->current_location);
        return;
    }
    if (bool_no_item_at_current_location() && bool_player_is_the_only_character_at_current_location())
    {
        add_output("\t[Try 'look around'.]\n\n");
        return;
    }

    if (*command.object)
    {
        items_with_same_tag = retrieve_items(PLAYER->current_location->items, command.object);
        characters_with_same_tag = retrieve_characters(PLAYER->current_location->characters, command.object);

        bool_item_match = items_with_same_tag != NULL && items_with_same_tag[0] != NULL;
        bool_character_match = characters_with_same_tag != NULL && characters_with_same_tag[0] != NULL;

        bool_several_item_matches = bool_item_match && items_with_same_tag[1] != NULL;
        bool_several_character_matches = bool_character_match && characters_with_same_tag[1] != NULL;

        if (!bool_item_match && !bool_character_match)
        {
            memset(command.object, 0, sizeof(command.object));
        }
        else if (bool_several_item_matches && bool_several_character_matches)
        {
            add_output("There is more than one item and character in your vicinity for which this tag works.\n");
            memset(command.object, 0, sizeof(command.object));
        }
        else if (bool_several_item_matches)
        {
            add_output("There is more than one item in your vicinity for which this tag works.\n");
            memset(command.object, 0, sizeof(command.object));
        }
        else if (bool_several_character_matches)
        {
            add_output("There is more than one character in your vicinity for which this tag works.\n");
            memset(command.object, 0, sizeof(command.object));
        }
        else if (bool_item_match)
        {
            add_output("%s\n\n", items_with_same_tag[0]->description_detailed);
            event_player_finds_entry_doors_key(items_with_same_tag[0]->id);
        }
        else if (bool_character_match && characters_with_same_tag[0] == PLAYER)
        {
            /* 'look [player]' is the same as the 'character' command */
            execute_character();
        }
        else
        {
            add_output("%s\n\n", characters_with_same_tag[0]->description);
        }
    }

    if (!*command.object)
    {
        display_item_suggestions(PLAYER->current_location->items, "look");
        display_character_suggestions(PLAYER->current_location->characters, "look");
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

