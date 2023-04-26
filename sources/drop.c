#include "../headers/drop.h"
#include "../headers/main.h"
#include "../headers/commands.h"
#include "../headers/items.h"

static void drop_item(Item* item_to_drop);

void execute_drop(void)
{
    Item** items_with_same_tag = NULL;

    if (PLAYER->current_location->items[NBR_ITEMS - 1])
    {
        add_output("This place cannot hold any more item.\n\n");
        return;
    }
    else if (!PLAYER->inventory[0])
    {
        add_output("You have no item on you.\n\n");
        return;
    }
    else if (*command.object)
    {
        items_with_same_tag = retrieve_items(PLAYER->inventory, command.object);

        if (!items_with_same_tag || !items_with_same_tag[0])
        {
            memset(command.object, 0, sizeof(command.object));
        }
        else if (items_with_same_tag[1])
        {
            add_output("There is more than one item in your inventory for which this tag works.\n\n");
            display_item_suggestions(items_with_same_tag, "drop");
        }
        else if (PLAYER->current_location->items[NBR_ITEMS - 1])
        {
            add_output("The current location is full. No more items can be added.\n\n");
        }
        else
        {
            drop_item(items_with_same_tag[0]);
        }
    }

    if (!*command.object)
        display_item_suggestions(PLAYER->inventory, "drop");

    free(items_with_same_tag);
    return;
}

static void drop_item(Item* item_to_drop)
{
    int i;
    int index_of_last_inventory_item = 0;

    for (i = 0; i < NBR_ITEMS; ++i)
    {
        /* Look for an empty spot in the current location's item list */
        if (!PLAYER->current_location->items[i])
        {
            /* Put the dropped item there */
            PLAYER->current_location->items[i] = item_to_drop;
            break;
        }
    }

    for (i = NBR_ITEMS - 1; i >= 0; --i)
    {
        /*
            Dropping the item is likely to leave a gap in the inventory.
            Therefore, look for the last item of the inventory as to later 
            put it in the dropped item's place.
        */
        if (!PLAYER->inventory[i])
            continue;
        else
            index_of_last_inventory_item = i;

        /* Remove the dropped item from the inventory */
        if (PLAYER->inventory[i] == item_to_drop)
        {
            memset((PLAYER->inventory + i), 0, sizeof(Item*));
            break;
        }
    }

    /* Fill the gap */
    if (i != index_of_last_inventory_item)
    {
        PLAYER->inventory[i] = PLAYER->inventory[index_of_last_inventory_item];
        memset((PLAYER->inventory + index_of_last_inventory_item), 0, sizeof(Item*));
    }

    add_output("'%s' dropped.\n\n", item_to_drop->name);
    return;
}

