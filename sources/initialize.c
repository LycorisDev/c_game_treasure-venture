#include "../headers/initialize.h"
#include "../headers/lexicon.h"
#include "../headers/locations.h"
#include "../headers/items.h"
#include "../headers/characters.h"
#include "../headers/events.h"

#define NBR_LINES 105
    /* 105 because:
        "previous_location"
        id of previous_location
        "current_location"
        id of current_location
        "inventory"
        100 potential inventory items
    */
#define NBR_CHARACTERS_IN_LINE 56

void exit_file_corrupted(FILE* save_file)
{
    printf("\n\t[Error: The save file has been corrupted.]\n");
    printf("\t[It will be deleted and the game will close.]\n");
    fclose(save_file);
    remove("save.txt");
    exit(EXIT_FAILURE);
}

void initialize_game(FILE* save_file)
{
    int i, j;
    long id;
    char *end_ptr = NULL;
    char save_buffer[NBR_LINES][NBR_CHARACTERS_IN_LINE] = {0};
    populate_list_lexicon();
    populate_list_locations();
    populate_list_items();
    populate_list_characters();
    populate_list_events();
	
    if (save_file != NULL)
    {
        for (i = 0; i < NBR_LINES; ++i)
        {
            /* NBR_CHARACTERS_IN_LINE - 1 because of the null ending character */
            for (j = 0; j < (NBR_CHARACTERS_IN_LINE - 1); ++j)
            {
                save_buffer[i][j] = fgetc(save_file);

                /* end of the current line */
                if (save_buffer[i][j] == '\n')
                {
                    save_buffer[i][j] = '\0';
                    break;
                }
                /* end of file */
                else if  (save_buffer[i][j] == EOF)
                {
                    i = NBR_LINES;
                    break;
                }
            }
        }

        if (save_buffer[0] == NULL || strcmp(save_buffer[0], "previous_location"))
        {
            exit_file_corrupted(save_file);
        }
        else
        {
            id = strtol(save_buffer[1], &end_ptr, 10);
            /*
                save_buffer[1] is empty
                OR there was a non-digit character in there (could also be that the only character is non-digit)
                OR the number is not plausible
            */
            if (save_buffer[1] == end_ptr || *end_ptr != '\0' || (id < 1 || id > (NBR_LOCATIONS - 1)))
                exit_file_corrupted(save_file);
            else
                PLAYER->previous_location = list_locations + id;
        }

        if (save_buffer[2] == NULL || strcmp(save_buffer[2], "current_location"))
        {
            exit_file_corrupted(save_file);
        }
        else
        {
            id = strtol(save_buffer[3], &end_ptr, 10);
            if (save_buffer[3] == end_ptr || *end_ptr != '\0' || (id < 1 || id > (NBR_LOCATIONS - 1)))
                exit_file_corrupted(save_file);
            else
                PLAYER->current_location = list_locations + id;
        }

        if (save_buffer[4] == NULL || strcmp(save_buffer[4], "inventory"))
        {
            exit_file_corrupted(save_file);
        }
        else
        {
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                id = strtol(save_buffer[5 + i], &end_ptr, 10);
                if (save_buffer[5 + i] == end_ptr || *end_ptr != '\0' || (id < 1 || id > (NBR_ITEMS - 1)))
                    break;
                else
                    PLAYER->list_of_items_by_id[i] = id;
            }
        }
    }
    return;
}

