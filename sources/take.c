#include "../headers/take.h"
#include "../headers/commands.h"
#include "../headers/items.h"

void execute_take(void)
{
    int i, j;
    int id_of_takeable_items[NBR_ITEMS] = {0};
    SameTag* takeable_items_with_same_tag = NULL;

    if (PLAYER->inventory[NBR_ITEMS - 1] != ID_ITEM_NONE)
    {
        printf("\nYour inventory is full.\n\n");
        return;
    }

    for (i = 0, j = 0; i < NBR_ITEMS; ++i)
    {
        if (PLAYER->current_location->list_of_items_by_id[i] == ID_ITEM_NONE)
            break;
        if (list_items[PLAYER->current_location->list_of_items_by_id[i]].can_be_taken == 1)
            id_of_takeable_items[j++] = PLAYER->current_location->list_of_items_by_id[i];
    }

    if (id_of_takeable_items[0] == ID_ITEM_NONE)
    {
        printf("\nThere is nothing for you to take here.\n\n");
        return;
    }

    if (strcmp(command.object, "") != 0)
    {
        takeable_items_with_same_tag = retrieve_takeable_item_id_by_parser_from_current_location(command.object);

        if (!takeable_items_with_same_tag || takeable_items_with_same_tag[0].id == ID_ITEM_NONE)
        {
            memcpy(command.object, "", BIG_LENGTH_WORD);
        }
        else if (takeable_items_with_same_tag[1].id == ID_ITEM_NONE)
        {
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                if (PLAYER->inventory[i] == ID_ITEM_NONE)
                {
                    PLAYER->inventory[i] = takeable_items_with_same_tag[0].id;
                    PLAYER->current_location->list_of_items_by_id[takeable_items_with_same_tag[0].index] = ID_ITEM_NONE;

                    for (j = NBR_ITEMS - 1; j >= 0; --j)
                    {
                        if (PLAYER->current_location->list_of_items_by_id[j] != ID_ITEM_NONE)
                        {
                            if (j != takeable_items_with_same_tag[0].index)
                            {
                                PLAYER->current_location->list_of_items_by_id[takeable_items_with_same_tag[0].index] = PLAYER->current_location->list_of_items_by_id[j];
                                PLAYER->current_location->list_of_items_by_id[j] = ID_ITEM_NONE;
                            }
                            break;
                        }
                    }
                    break;
                }
            }

            EVENT_PLAYER_FINDS_ENTRY_DOORS_KEY(takeable_items_with_same_tag[0].id)
            printf("\n'%s' added to your inventory.\n\n", list_items[takeable_items_with_same_tag[0].id].name);
        }
        else
        {
            /* TODO */
            printf("\nThere is more than one takeable item in your vicinity for which this tag works.\n");
            memcpy(command.object, "", BIG_LENGTH_WORD);
        }
    }

    if (strcmp(command.object, "") == 0)
    {
        if (id_of_takeable_items[1] == ID_ITEM_NONE)
        {
            printf("\n\t[Take what? Try 'take %s'.]\n\n", list_items[id_of_takeable_items[0]].tags[0]);
        }
        else
        {
            printf("\n\t[Take what? Try:]\n");
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                if (id_of_takeable_items[i] == ID_ITEM_NONE)
                    break;
                printf("\t\t['Take %s'.]\n", list_items[id_of_takeable_items[i]].tags[0]);
            }
            printf("\n");
        }
    }

    free(takeable_items_with_same_tag);
    return;
}

