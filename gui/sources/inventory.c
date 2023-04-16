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
        write_line("\nYou have no item on you.\n\n");
    }
    else if (!*command.object)
    {
        write_line("\n--------------------\n");
        write_line("INVENTORY\n\n");
        write_line("\t['Inventory [item]' to see the detailed description of an item.]\n\n");
        for (i = 0; i < NBR_ITEMS; ++i)
        {
            if (!PLAYER->inventory[i])
                break;
            write_line("- [%s]\n\t%s\n", PLAYER->inventory[i]->tags[0], PLAYER->inventory[i]->description_brief);
        }
        write_line("--------------------\n\n");
    }
    else
    {
        items_with_same_tag = retrieve_items_by_parser_from_inventory(command.object);

        if (!items_with_same_tag || !items_with_same_tag[0])
            write_line("\nYou have no such item on you. Type 'inventory' to see your items.\n\n");
        else if (!items_with_same_tag[1])
            write_line("\n%s\n\n", items_with_same_tag[0]->description_detailed);
        else
            write_line("\nThere is more than one item in your inventory for which this tag works.\n\n");
    }

    free(items_with_same_tag);
    return;
}

