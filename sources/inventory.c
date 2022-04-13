#include "../headers/inventory.h"
#include "../headers/commands.h"
#include "../headers/characters.h"
#include "../headers/items.h"

void execute_inventory(void)
{
    int i;
    SameTag* items_with_same_tag = NULL;

    if (PLAYER->inventory[0] == ID_ITEM_NONE)
    {
        printf("\nYou have no item on you.\n\n");
    }
    else if (strcmp(command.object, "") == 0)
    {
        printf("\n--------------------\n");
        printf("INVENTORY\n\n");
        printf("\t['Inventory [item]' to see the detailed description of an item.]\n\n");
        for (i = 0; i < NBR_ITEMS; ++i)
        {
            if (PLAYER->inventory[i] == ID_ITEM_NONE)
                break;
            printf("- [%s] / %s\n", list_items[PLAYER->inventory[i]].tags[0], list_items[PLAYER->inventory[i]].description_brief);
        }
        printf("--------------------\n\n");
    }
    else
    {
        items_with_same_tag = retrieve_item_id_by_parser_from_inventory(command.object);

        if (!items_with_same_tag || items_with_same_tag[0].id == ID_ITEM_NONE)
            printf("\nYou have no such item on you. Type 'inventory' to see your items.\n\n");
        else if (items_with_same_tag[1].id == ID_ITEM_NONE)
            printf("\n%s\n\n", list_items[items_with_same_tag[0].id].description_detailed);
        else
        {
            printf("\nThere is more than one item in your inventory for which this tag works.\n\n");
        }
    }

    free(items_with_same_tag);
    return;
}

