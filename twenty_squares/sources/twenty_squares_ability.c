#include "../headers/twenty_squares_ability.h"
#include "../headers/twenty_squares_selection.h"
#include "../../headers/input.h"
#include "../../headers/rng.h"

int set_ability(const int level, Cell*** target_cell, const Player* players, const Player* current_player)
{
    int i;
    int ability = ABILITY_NONE;

    if ((*(*target_cell))->is_cell_special)
    {
        ability = level > 2 ? get_random_number_minmax(2, 5) : ABILITY_CLASSIC;

        if (ability == ABILITY_FIRE)
        {
            if (current_player->id == 0)
            {
                /* No enemy of P1 on board OR enemies are protected by Earth: Fire is impossible --> replace with Water */
                if (PLAYER_TWO->number_of_stones_on_board == 0)
                    ability = ABILITY_WATER;
                else
                {
                    for (i = 0; i <= 7; ++i)
                    {
                        if (i == 7)
                            ability = ABILITY_WATER;

                        if (PLAYER_TWO->stoneset[i].coordinate > 2 && PLAYER_TWO->stoneset[i].protected_by_earth == 0)
                            break;
                    }
                }
            }
            else if (current_player->id == 1)
            {
                /* No enemy of P2 on board OR enemies are protected by Earth: Fire is impossible --> replace with Water */
                if (PLAYER_ONE->number_of_stones_on_board == 0)
                    ability = ABILITY_WATER;
                else
                {
                    for (i = 0; i <= 7; ++i)
                    {
                        if (i == 7)
                            ability = ABILITY_WATER;

                        if (PLAYER_ONE->stoneset[i].coordinate > 2 && PLAYER_ONE->stoneset[i].protected_by_earth == 0)
                            break;
                    }
                }
            }
        }
    }
    return ability;
}

void describe_ability(const int ability, const int dice)
{
    if (ability == ABILITY_CLASSIC)
    {
        printf("This Special Cell obtains the abilities 'Air' and 'Earth'.\n");
        printf("Effects: The current player gets a free turn and the stone is untouchable while standing on the cell.\n\n");
    }
    else if (ability == ABILITY_AIR)
    {
        printf("This Special Cell obtains the ability 'Air'.\n");
        printf("Effect: The current player gets a free turn.\n\n");
    }
    else if (ability == ABILITY_EARTH)
    {
        printf("This Special Cell obtains the ability 'Earth'.\n");
        printf("Effect: The stone is untouchable while standing on the cell.\n\n");
    }
    else if (ability == ABILITY_WATER)
    {
        printf("This Special Cell obtains the ability 'Water'.\n");
        printf("Effect: ");
        if (dice == 1)
            printf("Pick a living stone you want to put back to homebase.\n\n");
        else
            printf("From 1 to %d, pick living stones you want to put back to their respective homebase.\n\n", dice);
    }
    else if (ability == ABILITY_FIRE)
    {
        printf("This Special Cell obtains the ability 'Fire'.\n");
        printf("Effect: Pick an enemy stone standing on the board and not protected by Earth, and have it die.\n\n");
    }
    return;
}

int ds_stones_handle_ability(const Stone* chosen_stone, const int ability, const int level, const Player* current_player, const Player* other_player)
{
    if (chosen_stone->id == ID_STONE_GLUTTONY)
    {
        printf("Gluttony uses the ability. No waste.\n");
        return DS_DECISION_USE;
    }
    else if (chosen_stone->id == ID_STONE_SLOTH)
    {
        printf("Sloth discards the ability. Leave them alone.\n");
        return DS_DECISION_DISCARD;
    }
    else if (chosen_stone->id == ID_STONE_WRATH)
    {
        if (ability == ABILITY_WATER)
        {
            printf("Wrath discards the ability, because this one is not very... \"killing friendly.\"\n");
            return DS_DECISION_DISCARD;
        }
        else if (ability == ABILITY_AIR)
        {
            if (other_player->number_of_playable_stones == 0)
            {
                printf("Wrath discards the ability, because... What good would it be to play on a board devoid of enemies?\n");
                return DS_DECISION_DISCARD;
            }
            else if (chosen_stone->coordinate == current_player->racetrack[INDEX_3_ON_3_NO_KILLING_ROAD]->coordinate)
            {
                printf("Wrath uses the ability. This way, it can be used on a more useful stone.\n");
                return DS_DECISION_USE;
            }
            else
            {
                printf("Wrath uses the ability. One more chance to play! Please pick them! ...Pretty please?\n");
                return DS_DECISION_USE;
            }
        }
        else if (ability == ABILITY_FIRE)
        {
            printf("Wrath uses the ability. Haha, perfect! Don't run little stone... Not that you can anyway.\n");
            return DS_DECISION_USE;
        }
        else if (ability == ABILITY_EARTH)
        {
            if (chosen_stone->coordinate == current_player->racetrack[INDEX_3_ON_3_NO_KILLING_ROAD]->coordinate)
            {
                printf("Wrath discards the ability. There is no point in sticking around.\n");
                return DS_DECISION_DISCARD;
            }
            else
            {
                printf("Wrath uses the ability. With that, they will remain longer on the board... Even a bit is fine. Even one more stone.\n");
                return DS_DECISION_USE;
            }
        }
    }
    else
    {
        if (level > 2)
        {
            if (current_player->is_artificial_intelligence)
            {
                printf("%s lets %s decide what to do with the ability.\n", chosen_stone->name, current_player->name);
            }
            else
            {
                printf("%s lets you decide what to do with the ability.\n", chosen_stone->name);
                printf("If it's not used right away, it will be discarded.\n");
            }
        }
        return DS_DECISION_PLAYER;
    }
    /* We should never reach this return statement */
    return DS_DECISION_DISCARD;
}

void execute_ability_fire(const int level, Player* players, Player* current_player, Cell* all_cells)
{
    if (current_player->id)
    {
        printf("Fire will kill one of %s's stones.\n", PLAYER_ONE->name);
        remove_stone_from_board(all_cells, ABILITY_FIRE, level, PLAYER_ONE, current_player);
    }
    else
    {
        printf("Fire will kill one of %s's stones.\n", PLAYER_TWO->name);
        remove_stone_from_board(all_cells, ABILITY_FIRE, level, PLAYER_TWO, current_player);
    }
    return;
}

void execute_ability_water(const int dice, const int level, Player* players, Player* current_player, Cell* all_cells)
{
    int i;
    int selected_player = 0;
    int total_stones_on_board = PLAYER_ONE->number_of_stones_on_board + PLAYER_TWO->number_of_stones_on_board;
    int max_number_of_stones_to_select = total_stones_on_board < dice ? total_stones_on_board : dice;
    int number = max_number_of_stones_to_select == 1 ? 1 : select_number_of_stones_for_water(max_number_of_stones_to_select, current_player);

    printf("Water will wash %d %s away.\n", number, number == 1 ? "stone" : "stones");
    for (i = 0; i < number; ++i)
    {
        if (PLAYER_ONE->number_of_stones_on_board > 0 && PLAYER_TWO->number_of_stones_on_board > 0)
            selected_player = select_player_for_water(current_player);
        else if (PLAYER_ONE->number_of_stones_on_board > 0 && PLAYER_TWO->number_of_stones_on_board == 0)
            selected_player = 1;
        else if (PLAYER_ONE->number_of_stones_on_board == 0 && PLAYER_TWO->number_of_stones_on_board > 0)
            selected_player = 2;

        selected_player == 1 ? remove_stone_from_board(all_cells, ABILITY_WATER, level, PLAYER_ONE, current_player) 
                    : remove_stone_from_board(all_cells, ABILITY_WATER, level, PLAYER_TWO, current_player);
    }
    return;
}

void remove_stone_from_board(Cell* all_cells, const int ability, const int level, Player* targeted_player, Player* current_player)
{
    int i, j, random, is_input_valid = 0;
    int index_of_stones_on_board[7] = {0};
    char input[INPUT_SIZE];
    Stone* targeted_stone = NULL;

    if (current_player->is_artificial_intelligence)
    {
        printf("%s %s.\n", current_player->name, ability == ABILITY_FIRE ? "selects an enemy stone" : "selects a stone");

        for (i = 0, j = 0; i < 7; ++i)
        {
            if (targeted_player->stoneset[i].coordinate > 2)
            {
                if (ability == ABILITY_WATER || (ability == ABILITY_FIRE && targeted_player->stoneset[i].protected_by_earth == 0))
                    index_of_stones_on_board[j++] = i;
            }
        }

        random = get_random_number_minmax(0, j - 1);
        random = index_of_stones_on_board[random];
        targeted_stone = &(targeted_player->stoneset[random]);
    }
    else
    {
        printf("%s - Stone:\n", targeted_player->name);
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
                if (input[0] != '\0')
                    input[0] = toupper(input[0]);

                for (i = 0; i < 7; ++i)
                {
                    if (strcmp(targeted_player->stoneset[i].name, input) == 0 && targeted_player->stoneset[i].coordinate > 2 
                        && (ability == ABILITY_WATER || ((ability == ABILITY_FIRE && targeted_player->stoneset[i].protected_by_earth == 0))))
                    {
                        is_input_valid = 1;
                        targeted_stone = &(targeted_player->stoneset[i]);
                        break;
                    }
                }
            }

            flush_stdin();
            only_one_greaterthan_sign_is_printed();
        }
    }

    for (i = 0; i < 20; ++i)
    {
        if ((all_cells + i)->coordinate == targeted_stone->coordinate)
        {
            (all_cells + i)->stone_in_cell = NULL;
            targeted_stone->coordinate = ability == ABILITY_FIRE && (level == 2 || level == 4) ? -1 : 0;
            if (targeted_stone->coordinate == -1)
            {
                ++(current_player->points);
                --(targeted_player->points);
            }
            break;
        }
    }

    --(targeted_player->number_of_stones_on_board);
    printf("%s: %s.\n", targeted_player->name, targeted_stone->name);
    return;
}

