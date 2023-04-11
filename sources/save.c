#include "../headers/save.h"

void save_game(FILE* save_file)
{
    int i;

    f_write_line(save_file, "previous_location:%d\n", !PLAYER->previous_location ? -1 : PLAYER->previous_location->id);
    f_write_line(save_file, "current_location:%d\n", PLAYER->current_location->id);

    f_write_line(save_file, "events:");
    for (i = 0; i < NBR_EVENTS; ++i)
    {
        if (!i)
            f_write_line(save_file, "%d", list_events[i]);
        else
            f_write_line(save_file, ",%d", list_events[i]);
    }
    f_write_line(save_file, "\n");

    f_write_line(save_file, "inventory:");
    for (i = 0; i < NBR_ITEMS; ++i)
    {
        if (!PLAYER->inventory[i])
            break;

        if (!i)
            f_write_line(save_file, "%d", PLAYER->inventory[i]->id);
        else
            f_write_line(save_file, ",%d", PLAYER->inventory[i]->id);
    }
    f_write_line(save_file, "\n");

    return;
}

