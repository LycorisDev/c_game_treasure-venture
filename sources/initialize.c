#include "../headers/initialize.h"
#include "../headers/lexicon.h"
#include "../headers/locations.h"
#include "../headers/items.h"
#include "../headers/characters.h"
#include "../headers/events.h"

#define NBR_LINES (6 + NBR_EVENTS + NBR_ITEMS)
    /* Because:
        1. "previous_location"
        2. id of previous_location
        3. "current_location"
        4. id of current_location
        5. "events"
        6. "inventory"
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
	
    if (save_file)
    {
        for (i = 0; i < NBR_LINES; ++i)
        {
            /* NBR_CHARACTERS_IN_LINE - 1 because of the null ending character */
            for (j = 0; j < (NBR_CHARACTERS_IN_LINE - 1); ++j)
            {
                save_buffer[i][j] = fgetc(save_file);

                /* end of the current line (name:value,other_value\n) */
                if (save_buffer[i][j] == ':' || save_buffer[i][j] == ',' || save_buffer[i][j] == '\n')
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

        if (!save_buffer[0] || strcmp(save_buffer[0], "previous_location"))
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
            if (save_buffer[1] == end_ptr || *end_ptr != '\0' || (id < 0 || id > (NBR_LOCATIONS - 1)))
                exit_file_corrupted(save_file);
            else
                PLAYER->previous_location = list_locations + id;
        }

        if (!save_buffer[2] || strcmp(save_buffer[2], "current_location"))
        {
            exit_file_corrupted(save_file);
        }
        else
        {
            id = strtol(save_buffer[3], &end_ptr, 10);
            if (save_buffer[3] == end_ptr || *end_ptr != '\0' || (id < 0 || id > (NBR_LOCATIONS - 1)))
                exit_file_corrupted(save_file);
            else
            {
                /* The current location is full */
                if (PLAYER->current_location->characters[NBR_CHARACTERS - 1])
                    exit_file_corrupted(save_file);

                /* Update the player's current location */
                PLAYER->current_location = list_locations + id;

                if (PLAYER->current_location != LOCATION_OUTSIDE)
                {
                    /* Remove the player from the player's starter location (LOCATION_OUTSIDE) */
                    for (i = 0; i < NBR_CHARACTERS; ++i)
                    {
                        if (!LOCATION_OUTSIDE->characters[i])
                            break;

                        if (LOCATION_OUTSIDE->characters[i] == PLAYER)
                        {
                            for (j = NBR_CHARACTERS - 1; j >= 0; --j)
                            {
                                if (LOCATION_OUTSIDE->characters[j])
                                {
                                    LOCATION_OUTSIDE->characters[i] = LOCATION_OUTSIDE->characters[j];
                                    memset((LOCATION_OUTSIDE->characters + j), 0, sizeof(Character*));

                                    i = NBR_CHARACTERS;
                                    break;
                                }
                            }
                        }
                    }

                    /* Add the player to the current location */
                    for (i = 0; i < NBR_CHARACTERS; ++i)
                    {
                        if (!PLAYER->current_location->characters[i])
                        {
                            PLAYER->current_location->characters[i] = PLAYER;
                            break;
                        }
                    }
                }
            }
        }

        if (!save_buffer[4] || strcmp(save_buffer[4], "events"))
        {
            exit_file_corrupted(save_file);
        }
        else
        {
            for (i = 0; i < NBR_EVENTS; ++i)
            {
                id = strtol(save_buffer[5 + i], &end_ptr, 10);
                if (id != FLAG_ON && id != FLAG_OFF)
                    exit_file_corrupted(save_file);
                else if (id == FLAG_OFF)
                {
                    switch (i)
                    {
                        case 0:
                            EXECUTE_EVENT_PLAYER_ENTERS_MANSION_FOR_THE_FIRST_TIME
                            break;
                        case 1:
                            EXECUTE_EVENT_PLAYER_FINDS_ENTRY_DOORS_KEY
                            break;
                    }
                }
            }
        }

        if (!save_buffer[5 + NBR_EVENTS] || strcmp(save_buffer[5 + NBR_EVENTS], "inventory"))
        {
            exit_file_corrupted(save_file);
        }
        else
        {
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                id = strtol(save_buffer[6 + NBR_EVENTS + i], &end_ptr, 10);
                if (save_buffer[6 + NBR_EVENTS + i] == end_ptr || *end_ptr != '\0' || (id < 1 || id > (NBR_ITEMS - 1)))
                    break;
                else
                    PLAYER->inventory[i] = (list_items + id);
            }
        }
    }
    return;
}

