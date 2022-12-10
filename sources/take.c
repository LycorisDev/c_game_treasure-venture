#include "../headers/take.h"
#include "../headers/commands.h"
#include "../headers/items.h"

void execute_take(void)
{
    int i, j;
    Item* all_takeable_items[NBR_ITEMS] = {0};
    Item** takeable_items_with_same_tag = NULL;

    for (i = 0, j = 0; i < NBR_ITEMS; ++i)
    {
        if (!PLAYER->current_location->items[i])
            break;
        if (PLAYER->current_location->items[i]->can_be_taken)
            all_takeable_items[j++] = PLAYER->current_location->items[i];
    }

    if (!all_takeable_items[0])
    {
        printf("\nThere is nothing for you to take here.\n\n");
        return;
    }

    if (PLAYER->inventory[NBR_ITEMS - 1])
    {
        printf("\nYour inventory is full.\n\n");
        return;
    }

    if (*command.object)
    {
        takeable_items_with_same_tag = retrieve_takeable_items_by_parser_from_current_location(command.object);

        if (!takeable_items_with_same_tag || !takeable_items_with_same_tag[0])
        {
            memset(command.object, 0, sizeof(command.object));
        }
        else if (!takeable_items_with_same_tag[1])
        {
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                /* Look for an empty spot in the inventory */
                if (!PLAYER->inventory[i])
                {
                    /* Put the taken item there */
                    PLAYER->inventory[i] = takeable_items_with_same_tag[0];

                    for (j = 0; j < NBR_ITEMS; ++j)
                    {
                        /* Find its copy in the current location */
                        if (PLAYER->current_location->items[j] == takeable_items_with_same_tag[0])
                        {
                            /* Empty this spot */
                            memset((PLAYER->current_location->items + j), 0, sizeof(Item*));

                            /* If the item wasn't in last position in the current location and the next spot has an item, there's now a hole */
                            if (j != NBR_ITEMS - 1 && PLAYER->current_location->items[j + 1])
                            {
                                for (i = NBR_ITEMS - 1; i >= 0; --i)
                                {
                                    /* Look for the last item of the current location */
                                    if (PLAYER->current_location->items[i])
                                    {
                                        /* Use it to fill the hole */
                                        PLAYER->current_location->items[j] = PLAYER->current_location->items[i];
                                        memset((PLAYER->current_location->items + i), 0, sizeof(Item*));
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

            EVENT_PLAYER_FINDS_ENTRY_DOORS_KEY((takeable_items_with_same_tag + 0))
            printf("\n'%s' added to your inventory.\n\n", takeable_items_with_same_tag[0]->name);
        }
        else
        {
            printf("\nThere is more than one takeable item in your vicinity for which this tag works.\n");
            memset(command.object, 0, sizeof(command.object));
        }
    }

    if (!*command.object)
    {
        if (!all_takeable_items[1])
        {
            printf("\n\t[Try 'take %s'.]\n\n", all_takeable_items[0]->tags[0]);
        }
        else
        {
            printf("\n\t[Try:]\n");
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                if (!all_takeable_items[i])
                    break;
                printf("\t\t['Take %s'.]\n", all_takeable_items[i]->tags[0]);
            }
            printf("\n");
        }
    }

    free(takeable_items_with_same_tag);
    return;
}

