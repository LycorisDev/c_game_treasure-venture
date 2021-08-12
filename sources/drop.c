#include "../headers/drop.h"
#include "../headers/commands.h"
#include "../headers/items.h"

void execute_drop(void)
{
    int i, j;
    int item_id = 0;

    if (PLAYER->current_location->list_of_items_by_id[NBR_ITEMS - 1] != ID_ITEM_NONE)
    {
        printf("\nThis place cannot hold any more item.\n\n");
        return;
    }

    if (PLAYER->list_of_items_by_id[0] == ID_ITEM_NONE)
    {
        printf("\nYou have no item on you.\n\n");
        return;
    }

    if (strcmp(command.object, "") != 0)
    {
        if ((item_id = retrieve_item_id_by_parser(command.object)) == ID_ITEM_NONE)
            memcpy(command.object, "", BIG_LENGTH_WORD);
        else
        {
            for (i = 0; i <= NBR_ITEMS; ++i)
            {
                if (i == NBR_ITEMS || PLAYER->list_of_items_by_id[i] == ID_ITEM_NONE)
                {
                    memcpy(command.object, "", BIG_LENGTH_WORD);
                    break;
                }
                else if (PLAYER->list_of_items_by_id[i] == item_id)
                {
                    for (j = 0; j < NBR_ITEMS; ++j)
                    {
                        if (PLAYER->current_location->list_of_items_by_id[j] == ID_ITEM_NONE)
                        {
                            PLAYER->current_location->list_of_items_by_id[j] = item_id;
                            PLAYER->list_of_items_by_id[i] = ID_ITEM_NONE;

                            for (j = NBR_ITEMS - 1; j >= 0; --j)
                            {
                                if (PLAYER->list_of_items_by_id[j] != ID_ITEM_NONE)
                                {
                                    if (i < j)
                                    {
                                        PLAYER->list_of_items_by_id[i] = PLAYER->list_of_items_by_id[j];
                                        PLAYER->list_of_items_by_id[j] = ID_ITEM_NONE;
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    printf("\n'%s' dropped.\n\n", list_items[item_id].name);
                    break;
                }
            }
        }
    }

    if (strcmp(command.object, "") == 0)
    {
        if (PLAYER->list_of_items_by_id[1] == ID_ITEM_NONE)
        {
            printf("\n\t[Drop what? Try 'drop %s'.]\n\n", retrieve_default_item_tag_by_id(PLAYER->list_of_items_by_id[0]));
        }
        else
        {
            printf("\n\t[Drop what? Try:]\n");
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                if (PLAYER->list_of_items_by_id[i] == ID_ITEM_NONE)
                    break;
                printf("\t\t['Drop %s'.]\n", retrieve_default_item_tag_by_id(PLAYER->list_of_items_by_id[i]));
            }
            printf("\n");
        }
    }
    return;
}

