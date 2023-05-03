#include "../headers/use.h"
#include "../headers/main.h"
#include "../headers/commands.h"
#include "../headers/items.h"
#include "../headers/characters.h"

static Item* find_item_to_use(void);
static void use_access_item(Item* item_to_use);
static int use_item_on_target(const Item* item_to_use);

void execute_use(void)
{
    Item* item_to_use = NULL;
    int bool_issue_is_target = 0;

    if (!PLAYER->inventory[0] && !PLAYER->current_location->items[0])
    {
        add_output("There is nothing for you to use.\n\n");
        return;
    }

    if (*command.object)
        item_to_use = find_item_to_use();

    if (item_to_use)
    {
        if (item_to_use->access)
            use_access_item(item_to_use);
        else if (item_to_use->bool_requires_target_for_use)
            bool_issue_is_target = use_item_on_target(item_to_use);
        else
        {
            add_output("%s ", item_to_use->description);
            add_output("The %s %s seem to be of much use.\n\n", item_to_use->tags[1], item_to_use->bool_is_singular ? "doesn't" : "don't");
        }
    }

    if (bool_issue_is_target)
    {
        
    }
    else if (!*command.object)
    {
        display_item_suggestions(PLAYER->inventory, "use");
        display_item_suggestions(PLAYER->current_location->items, "use");
    }

    return;
}

static Item* find_item_to_use(void)
{
    Item* item_to_use = NULL;
    Item** inventory_items = retrieve_items(PLAYER->inventory, command.object);
    Item** location_items = retrieve_items(PLAYER->current_location->items, command.object);
    int bool_inventory_match = inventory_items && inventory_items[0];
    int bool_location_match = location_items && location_items[0];

    if (bool_inventory_match && bool_location_match)
    {
        add_output("Your inventory and vicinity both included, there is more than one item for which this tag works.\n");
        memset(command.object, 0, sizeof(command.object));
    }
    else if (bool_inventory_match)
    {
        if (inventory_items[1])
        {
            add_output("There is more than one item in your inventory for which this tag works.\n");
            memset(command.object, 0, sizeof(command.object));
        }
        else
        {
            item_to_use = inventory_items[0];
        }
    }
    else if (bool_location_match)
    {
        if (location_items[1])
        {
            add_output("There is more than one item in your vicinity for which this tag works.\n");
            memset(command.object, 0, sizeof(command.object));
        }
        else
        {
            item_to_use = location_items[0];
        }
    }
    else
    {
        memset(command.object, 0, sizeof(command.object));
    }

    free(inventory_items);
    free(location_items);
    return item_to_use;
}

static void use_access_item(Item* item_to_use)
{
    if (item_to_use->access == ACCESS_OPEN)
    {
        item_to_use->access = ACCESS_CLOSED;
        add_output("You close the %s.\n\n", item_to_use->bool_is_singular ? "door" : "doors");
    }
    else if (item_to_use->access == ACCESS_CLOSED)
    {
        item_to_use->access = ACCESS_OPEN;
        add_output("You open the %s.\n\n", item_to_use->bool_is_singular ? "door" : "doors");
    }
    else
    {
        add_output("The %s %s locked.\n\n", item_to_use->bool_is_singular ? "door" : "doors", item_to_use->bool_is_singular ? "is" : "are");
    }
    return;
}

static int use_item_on_target(const Item* item_to_use)
{
    void* target = NULL;
    Item** items = NULL;
    Character** characters = NULL;
    int bool_item_match = 0;
    int bool_character_match = 0;
    int bool_target_is_character = 0;

    if (!*command.target || !*command.preposition || strcmp(command.preposition, "on"))
    {
        add_output("Use the %s on who or what?\n\n", command.object);
        return 1;
    }

    items = retrieve_items(PLAYER->current_location->items, command.target);
    characters = retrieve_characters(PLAYER->current_location->characters, command.target);
    bool_item_match = items && items[0];
    bool_character_match = characters && characters[0];

    if (bool_item_match && bool_character_match)
    {
        add_output("There is more than one target in your vicinity for which this tag works.\n\n");
    }
    else if (bool_item_match)
    {
        if (items[1])
            add_output("There is more than one item in your vicinity for which this tag works.\n\n");
        else
            target = items[0];
    }
    else if (bool_character_match)
    {
        if (characters[1])
            add_output("There is more than one character in your vicinity for which this tag works.\n\n");
        else
        {
            target = characters[0];
            bool_target_is_character = 1;
        }
    }
    else
    {
        add_output("Use the %s on who or what?\n\n", command.object);
    }

    if (!target)
    {
        free(items);
        free(characters);
        return 1;
    }

    if (bool_target_is_character)
    {
        if (target == PLAYER)
            add_output("The %s %s nothing to you.\n\n", item_to_use->tags[1], item_to_use->bool_is_singular ? "does" : "do");
        else
            add_output("The %s %s nothing to the %s.\n\n", item_to_use->tags[1], item_to_use->bool_is_singular ? "does" : "do", ((Character*)target)->tags[1]);
    }
    else if (!((Item*)target)->access || ((Item*)target)->unlocked_with != item_to_use)
    {
        add_output("The %s %s nothing to the %s.\n\n", item_to_use->tags[1], item_to_use->bool_is_singular ? "does" : "do", ((Item*)target)->tags[1]);
    }
    else if (((Item*)target)->access == ACCESS_OPEN)
    {
        ((Item*)target)->access = ACCESS_LOCKED;
        add_output("You close and lock the %s.\n\n", ((Item*)target)->bool_is_singular ? "door" : "doors");
    }
    else if (((Item*)target)->access == ACCESS_CLOSED)
    {
        ((Item*)target)->access = ACCESS_LOCKED;
        add_output("You lock the %s.\n\n", ((Item*)target)->bool_is_singular ? "door" : "doors");
    }
    else
    {
        ((Item*)target)->access = ACCESS_CLOSED;
        add_output("You unlock the %s.\n\n", ((Item*)target)->bool_is_singular ? "door" : "doors");
    }

    free(items);
    free(characters);
    return 0;
}

