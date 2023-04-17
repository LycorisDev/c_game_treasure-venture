#include "../headers/inventory.h"
#include "../headers/main.h"
#include "../headers/commands.h"
#include "../headers/characters.h"
#include "../headers/items.h"

void execute_inventory(void)
{
    int i;
    Item** items_with_same_tag = NULL;

    if (!PLAYER->inventory[0])
    {
        add_output("\nYou have no item on you.\n\n");
    }
    else if (!*command.object)
    {
        add_output("\n--------------------\n");
        add_output("INVENTORY\n\n");
        add_output("\t['Inventory [item]' to see the detailed description of an item.]\n\n");
        for (i = 0; i < NBR_ITEMS; ++i)
        {
            if (!PLAYER->inventory[i])
                break;
            add_output("- [%s]\n\t%s\n", PLAYER->inventory[i]->tags[0], PLAYER->inventory[i]->description_brief);
        }
        add_output("--------------------\n\n");
    }
    else
    {
        items_with_same_tag = retrieve_items_by_parser_from_inventory(command.object);

        if (!items_with_same_tag || !items_with_same_tag[0])
            add_output("\nYou have no such item on you. Type 'inventory' to see your items.\n\n");
        else if (!items_with_same_tag[1])
            add_output("\n%s\n\n", items_with_same_tag[0]->description_detailed);
        else
            add_output("\nThere is more than one item in your inventory for which this tag works.\n\n");
    }

    free(items_with_same_tag);
    return;
}

