#include "../headers/save.h"

void save_game(FILE* save_file)
{
    int i;

    fprintf(save_file, "current_location\n");
    fprintf(save_file, "%d\n", PLAYER->current_location->location_id);

    fprintf(save_file, "inventory\n");
    for (i = 0; i < NBR_ITEMS; ++i)
    {
        if (PLAYER->list_of_items_by_id[i] == ID_ITEM_NONE)
            break;
        fprintf(save_file, "%d\n", PLAYER->list_of_items_by_id[i]);
    }

    return;
}

