#include "../headers/take.h"
#include "../headers/main.h"
#include "../headers/commands.h"
#include "../headers/items.h"

static void take_item(Item* item_to_take);
static void clean(Item** p1, Item** p2);

void execute_take(void)
{
    Item** takeable_items = retrieve_takeable_items(PLAYER->current_location->items, NULL);
    Item** takeable_items_with_same_tag = NULL;

    if (!takeable_items || !takeable_items[0])
    {
        add_output("There is nothing for you to take here.\n\n");
        clean(takeable_items, takeable_items_with_same_tag);
        return;
    }

    if (PLAYER->inventory[NBR_ITEMS - 1])
    {
        add_output("Your inventory is full.\n\n");
        clean(takeable_items, takeable_items_with_same_tag);
        return;
    }

    if (!*command.object)
    {
        display_item_suggestions(takeable_items, "take");
        clean(takeable_items, takeable_items_with_same_tag);
        return;
    }

    takeable_items_with_same_tag = retrieve_takeable_items(takeable_items, command.object);
    if (!takeable_items_with_same_tag || !takeable_items_with_same_tag[0])
    {
        display_item_suggestions(takeable_items, "take");
        clean(takeable_items, takeable_items_with_same_tag);
        return;
    }

    if (takeable_items_with_same_tag[1])
    {
        add_output("There is more than one takeable item in your vicinity for which this tag works.\n");
        display_item_suggestions(takeable_items, "take");
        clean(takeable_items, takeable_items_with_same_tag);
        return;
    }

    take_item(takeable_items_with_same_tag[0]);
    clean(takeable_items, takeable_items_with_same_tag);
    return;
}

static void take_item(Item* item_to_take)
{
    int i;
    int index_of_last_location_item = -1;
    
    /* Place the item in the inventory */
    for (i = 0; i < NBR_ITEMS; ++i)
    {
        if (!PLAYER->inventory[i])
        {
            PLAYER->inventory[i] = item_to_take;
            break;
        }
    }

    /* Remove the item from the location */
    for (i = NBR_ITEMS - 1; i >= 0; --i)
    {
        if (!PLAYER->current_location->items[i])
            continue;
        else
            index_of_last_location_item = i;

        if (PLAYER->current_location->items[i] == item_to_take)
        {
            memset((PLAYER->current_location->items + i), 0, sizeof(Item*));
            break;
        }
    }

    /* Fill the gap */
    if (i != index_of_last_location_item)
    {
        PLAYER->current_location->items[i] = PLAYER->current_location->items[index_of_last_location_item];
        memset((PLAYER->current_location->items + index_of_last_location_item), 0, sizeof(Item*));
    }

    event_player_finds_entry_doors_key(item_to_take->id);
    add_output("'%s' added to your inventory.\n\n", item_to_take->name);
    return;
}

static void clean(Item** p1, Item** p2)
{
    free(p1);
    free(p2);
    return;
}

