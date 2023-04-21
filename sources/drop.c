#include "../headers/drop.h"
#include "../headers/main.h"
#include "../headers/commands.h"
#include "../headers/items.h"

void execute_drop(void)
{
    int i, j;
    Item** items_with_same_tag = NULL;

    if (PLAYER->current_location->items[NBR_ITEMS - 1])
    {
        add_output("\nThis place cannot hold any more item.\n\n");
        return;
    }
    else if (!PLAYER->inventory[0])
    {
        add_output("\nYou have no item on you.\n\n");
        return;
    }
    else if (*command.object)
    {
        items_with_same_tag = retrieve_items_by_parser_from_inventory(command.object);

        if (!items_with_same_tag || !items_with_same_tag[0])
        {
            memset(command.object, 0, sizeof(command.object));
        }
        else if (items_with_same_tag[1])
        {
            add_output("\nThere is more than one item in your inventory for which this tag works.\n\n");
            add_output("\n\t[Try:]\n");
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                if (!items_with_same_tag[i])
                    break;
                add_output("\t\t['Drop %s'.]\n", items_with_same_tag[i]->tags[0]);
            }
            add_output("\n");
        }
        else if (PLAYER->current_location->items[NBR_ITEMS - 1])
        {
            add_output("\nThe current location is full. No more items can be added.\n\n");
        }
        else
        {
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                /* Look for an empty spot in the current location's item list */
                if (!PLAYER->current_location->items[i])
                {
                    /* Put the dropped item there */
                    PLAYER->current_location->items[i] = items_with_same_tag[0];

                    for (j = 0; j < NBR_ITEMS; ++j)
                    {
                        /* Find its copy in the inventory */
                        if (PLAYER->inventory[j] == items_with_same_tag[0])
                        {
                            /* Empty this spot */
                            memset((PLAYER->inventory + j), 0, sizeof(Item*));

                            /* If the item wasn't in last position in the inventory and the next spot has an item, there's now a hole */
                            if (j != NBR_ITEMS - 1 && PLAYER->inventory[j + 1])
                            {
                                for (i = NBR_ITEMS - 1; i >= 0; --i)
                                {
                                    /* Look for the last item of the inventory */
                                    if (PLAYER->inventory[i])
                                    {
                                        /* Use it to fill the hole */
                                        PLAYER->inventory[j] = PLAYER->inventory[i];
                                        memset((PLAYER->inventory + i), 0, sizeof(Item*));
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
            }
            add_output("\n'%s' dropped.\n\n", items_with_same_tag[0]->name);
        }
    }

    if (!*command.object)
    {
        if (!PLAYER->inventory[1])
        {
            add_output("\n\t[Try 'drop %s'.]\n\n", PLAYER->inventory[0]->tags[0]);
        }
        else
        {
            add_output("\n\t[Try:]\n");
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                if (!PLAYER->inventory[i])
                    break;
                add_output("\t\t['Drop %s'.]\n", PLAYER->inventory[i]->tags[0]);
            }
            add_output("\n");
        }
    }

    free(items_with_same_tag);
    return;
}

