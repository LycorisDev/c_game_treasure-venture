#include "../headers/twenty_squares_selection.h"
#include "../../headers/input.h"
#include "../../headers/rng.h"

Stone* select_stone(char* input, Player* current_player)
{
    int i, j, random;
    int is_input_valid = 0;
    int number_of_moveable_stones = 0;
    char moveable_stones_names[8][LENGTH_STONE_NAME] = {0};
    Stone* chosen_stone;

    /* Print the available choices + set moveable_stones_names[] and number_of_moveable_stones at the same time */
    printf("Stone:\n");
    memcpy(moveable_stones_names[0], "quit", LENGTH_STONE_NAME);
    for (i = 0, j = 1; i < 7; ++i)
    {
        if (current_player->stoneset[i].can_stone_move)
        {
            printf("- %s ", current_player->stoneset[i].name);
            memcpy(moveable_stones_names[j++], current_player->stoneset[i].name, LENGTH_STONE_NAME);
        }
    }
    number_of_moveable_stones = j - 1;
    printf("-\n\n");

    if (current_player->is_artificial_intelligence)
    {
        random = get_random_number_minmax(1, number_of_moveable_stones);
        for (i = 0; i < 7; ++i)
        {
            if (strcmp(current_player->stoneset[i].name, moveable_stones_names[random]) == 0)
            {
                memcpy(input, moveable_stones_names[random], LENGTH_STONE_NAME);
                chosen_stone = &(current_player->stoneset[i]);
                printf("Stone: %s.\n\n", input);
                break;
            }
        }
    }
    else
    {
        for (i = 1; i < 8; ++i)
            moveable_stones_names[i][0] = tolower(moveable_stones_names[i][0]);

        /* number_of_moveable_stones is incremented to take "quit" into account in the for loop */
        ++number_of_moveable_stones;
        while (!is_input_valid)
        {
            printf("> ");
            if (fgets(input, INPUT_SIZE, stdin) != NULL)
            {
                for (i = 0; i < INPUT_SIZE; ++i)
                {
                    if (input[i] == '\n')
                    {
                        input[i] = '\0';
                        break;
                    }
                    input[i] = tolower(input[i]);
                }

                for (i = 0; i < number_of_moveable_stones; ++i)
                {
                    if (strcmp(input, moveable_stones_names[i]) == 0)
                    {
                        is_input_valid = 1;
                        break;
                    }
                }
            }

            flush_stdin();
            only_one_greaterthan_sign_is_printed();
        }

        if (strcmp(input, "quit") != 0)
        {
            input[0] = toupper(input[0]);
            printf("\nStone: %s.\n\n", input);
            for (i = 0; i < 7; ++i)
            {
                if (strcmp(current_player->stoneset[i].name, input) == 0)
                {
                    chosen_stone = &(current_player->stoneset[i]);
                    break;
                }
            }
        }
    }
    return chosen_stone;
}

int select_number_of_cells_forward(const Player* current_player, const Stone* chosen_stone)
{
    int i, min_index = -1, max_index, chosen_number;
    int is_chosen_number_valid = 0;
    char input[8] = {0};
    for (i = 0; i < 4; ++i)
    {
        if (chosen_stone->possible_movements[i])
        {
            if (min_index < 0)
                min_index = i;
            max_index = i;
        }
    }

    /*
    Lust doesn't have a special move.
    Pride is handled in move_stone().
    Wrath and Greed are handled in can_this_ds_stone_move().
    */

    if (min_index == max_index || chosen_stone->id == ID_STONE_GLUTTONY)
    {
        chosen_number = chosen_stone->possible_movements[max_index];
    }
    else if (chosen_stone->id == ID_STONE_SLOTH)
    {
        chosen_number = chosen_stone->possible_movements[min_index];
    }
    else if (current_player->is_artificial_intelligence || chosen_stone->id == ID_STONE_ENVY)
    {
        chosen_number = chosen_stone->possible_movements[get_random_number_minmax(min_index, max_index)];
    }
    else
    {
        printf("How many cells forwards should the stone move? ");
        for (i = min_index; i <= max_index; ++i)
        {
            if (i == max_index)
                printf("%d.\n\n", chosen_stone->possible_movements[i]);
            else
                printf("%d - ", chosen_stone->possible_movements[i]);
        }

        while (!is_chosen_number_valid)
        {
            printf("> ");
            if (fgets(input, 8, stdin) != NULL)
            {
                chosen_number = atoi(input);
                for (i = min_index; i <= max_index; ++i)
                {
                    if (chosen_number == chosen_stone->possible_movements[i])
                    {
                        is_chosen_number_valid = 1;
                        break;
                    }
                }
            }
            flush_stdin();
            only_one_greaterthan_sign_is_printed();
        }
        printf("\n");
    }

    printf("Movement: %d %s forwards.\n", chosen_number, chosen_number == 1 ? "cell" : "cells");
    return chosen_number;
}

void select_use_ability(char* input, const Player* current_player, const int ability, const int ds_decision, Cell*** target_cell)
{
    int i;
    int is_input_valid = 0;
    char choices[3][INPUT_SIZE] = {0};

    if (ability == ABILITY_CLASSIC || ds_decision == DS_DECISION_USE)
    {
        memcpy(input, "yes", INPUT_SIZE);
        return;
    }
    else if (ds_decision == DS_DECISION_DISCARD)
    {
        memcpy(input, "no", INPUT_SIZE);
        return;
    }

    if (current_player->is_artificial_intelligence)
    {
        if (ability == ABILITY_EARTH && (*(*target_cell))->coordinate == current_player->racetrack[INDEX_2_ON_2_END_ROAD]->coordinate)
            memcpy(input, "no", INPUT_SIZE);
        else
        {
            if (get_random_number_minmax(0, 1))
                memcpy(input, "yes", INPUT_SIZE);
            else
                memcpy(input, "no", INPUT_SIZE);
        }
    }
    else
    {
        memcpy(choices[0], "quit", INPUT_SIZE);
        memcpy(choices[1], "yes", INPUT_SIZE);
        memcpy(choices[2], "no", INPUT_SIZE);
        printf("Do you use the ability? Yes/No\n\n");

        while (!is_input_valid)
        {
            printf("> ");
            if (fgets(input, INPUT_SIZE, stdin) != NULL)
            {
                for (i = 0; i < INPUT_SIZE; ++i)
                {
                    if (input[i] == '\n')
                    {
                        input[i] = '\0';
                        break;
                    }
                    input[i] = tolower(input[i]);
                }

                for (i = 0; i < 3; ++i)
                {
                    if (strcmp(input, choices[i]) == 0)
                    {
                        is_input_valid = 1;
                        break;
                    }
                }
            }

            flush_stdin();
            only_one_greaterthan_sign_is_printed();
        }
        if (strcmp(input, "quit") != 0)
            printf("\n");
    }

    if (strcmp(input, "yes") == 0)
        printf("%s uses the ability.\n\n", current_player->name);
    else if (strcmp(input, "no") == 0)
        printf("%s discards the ability.\n\n", current_player->name);
    return;
}

int select_number_of_stones_for_water(const int max_number, const Player* current_player)
{
    if (current_player->is_artificial_intelligence)
    {
        printf("%s chooses the number of stones they'll pick.\n", current_player->name);
        return get_random_number_minmax(1, max_number);
    }
    else
    {
        return get_number_input(1, max_number, "How many stones do you pick?");
    }
}

int select_player_for_water(const Player* current_player)
{
    if (current_player->is_artificial_intelligence)
        return get_random_number_minmax(1, 2);
    else
        return get_number_input(1, 2, "Player: ");
}

