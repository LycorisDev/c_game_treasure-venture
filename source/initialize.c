#include "../headers/initialize.h"
#include "../headers/lexicon.h"
#include "../headers/locations.h"
#include "../headers/items.h"
#include "../headers/characters.h"

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
    char save_buffer[4][56] = {0};
    populate_list_lexicon();
    populate_list_locations();
    populate_list_items();
    populate_list_characters();
	
    if (save_file != NULL)
    {
        for (i = 0; i < 4; ++i)
        {
            /* 55 characters and not 56 because of the null ending character */
            for (j = 0; j < 55; ++j)
            {
                save_buffer[i][j] = fgetc(save_file);
                if (save_buffer[i][j] == '\n')
                {
                    save_buffer[i][j] = '\0';
                    break;
                }
            }
        }

        if (save_buffer[0] == NULL || strcmp(save_buffer[0], "current_location"))
        {
            exit_file_corrupted(save_file);
        }
        else
        {
            id = strtol(save_buffer[1], &end_ptr, 10);
            /* save_buffer[2] is empty */
            /* OR there was a non-digit character in there (could also be that the only character is non-digit) */
            /* OR the number is not plausible */
            if (save_buffer[1] == end_ptr || *end_ptr != '\0' || (id < 1 || id > (NBR_LOCATIONS - 1)))
                exit_file_corrupted(save_file);
            else
                PLAYER->current_location = list_locations + id;
        }

        if (save_buffer[2] == NULL || strcmp(save_buffer[2], "debug_value"))
        {
            exit_file_corrupted(save_file);
        }
    }
    return;
}

