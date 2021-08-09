#include "../headers/save.h"

void save_game(FILE* save_file)
{
    fprintf(save_file, "current_location\n");
    fprintf(save_file, "%d\n", PLAYER->current_location->location_id);

    fprintf(save_file, "debug_value\n");
    fprintf(save_file, "%d\n", 42);

    return;
}

