#include "../headers/commands.h"

#include "../headers/play.h"
#include "../headers/inventory.h"
#include "../headers/character.h"
#include "../headers/go.h"
#include "../headers/look.h"
#include "../headers/take.h"
#include "../headers/drop.h"
#include "../headers/use.h"
#include "../headers/hold.h"

/* Declared as extern in ../headers/commands.h */
Command command;

void display_commands(void)
{
    printf("\n");
    printf("\t['Menu']    ['Inventory']    ['Go']      ['Take']    ['Use']\n");
    printf("\t['Play']    ['Character']    ['Look']    ['Drop']    ['Hold']\n");
    printf("\n");
    return;
}

void parse_game_command(void)
{
    int i, j, parser_matches_with_lexicon = 1, index_preposition = 0, index_stop_matching = -1, max = nbr_words_in_parser;
    char object_1[LENGTH_WORD], object_2[LENGTH_WORD], object_3[LENGTH_WORD];
    char target_1[LENGTH_WORD], target_2[LENGTH_WORD], target_3[LENGTH_WORD];
    memset(command.verb, 0, sizeof(command.verb));
    memset(command.object, 0, sizeof(command.object));
    memset(command.preposition, 0, sizeof(command.preposition));
    memset(command.target, 0, sizeof(command.target));

    if (parser[0])
    {
        for (i = 0; i < nbr_words_in_parser; ++i)
        {
            for (j = 0; j < NBR_WORDS; ++j)
            {
                if (!list_lexicon[j][0])
                {
                    parser_matches_with_lexicon = 0;
                    break;
                }

                if (!strcmp(parser[i], list_lexicon[j]))
                {
                    if (index_preposition == 0 && !strcmp(parser[i], "on"))
                        index_preposition = i >= 2 && i <= 4 ? i : -1;
                    break;
                }
            }

            if (!parser_matches_with_lexicon)
            {
                printf("\n\t['%s' was not recognized.]\n", parser[i]);
                index_stop_matching = i;
                break;
            }
        }

        max = index_stop_matching == -1 ? (nbr_words_in_parser - 1) : index_stop_matching;

        if (index_preposition == 2)
        {
            if (max >= 0)
            {
                memcpy(command.verb, parser[0], LENGTH_WORD);
                if (max >= 1)
                {
                    memcpy(object_1, parser[1], LENGTH_WORD);
                    if (max >= 2)
                    {
                        memcpy(command.preposition, parser[2], LENGTH_WORD);
                        if (max >= 3)
                        {
                            memcpy(target_1, parser[3], LENGTH_WORD);
                            if (max >= 4)
                            {
                                memcpy(target_2, parser[4], LENGTH_WORD);
                                if (max >= 5)
                                    memcpy(target_3, parser[5], LENGTH_WORD);
                            }
                        }
                    }
                }
            }
        }
        else if (index_preposition == 3)
        {
            if (max >= 0)
            {
                memcpy(command.verb, parser[0], LENGTH_WORD);
                if (max >= 1)
                {
                    memcpy(object_1, parser[1], LENGTH_WORD);
                    if (max >= 2)
                    {
                        memcpy(object_2, parser[2], LENGTH_WORD);
                        if (max >= 3)
                        {
                            memcpy(command.preposition, parser[3], LENGTH_WORD);
                            if (max >= 4)
                            {
                                memcpy(target_1, parser[4], LENGTH_WORD);
                                if (max >= 5)
                                {
                                    memcpy(target_2, parser[5], LENGTH_WORD);
                                    if (max >= 6)
                                        memcpy(target_3, parser[6], LENGTH_WORD);
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if (max >= 0)
            {
                memcpy(command.verb, parser[0], LENGTH_WORD);
                if (max >= 1)
                {
                    memcpy(object_1, parser[1], LENGTH_WORD);
                    if (max >= 2)
                    {
                        memcpy(object_2, parser[2], LENGTH_WORD);
                        if (max >= 3)
                        {
                            memcpy(object_3, parser[3], LENGTH_WORD);
                            if (max >= 4)
                            {
                                memcpy(command.preposition, parser[4], LENGTH_WORD);
                                if (max >= 5)
                                {
                                    memcpy(target_1, parser[5], LENGTH_WORD);
                                    if (max >= 6)
                                    {
                                        memcpy(target_2, parser[6], LENGTH_WORD);
                                        if (max >= 7)
                                            memcpy(target_3, parser[7], LENGTH_WORD);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if (*object_1)
        {
            if (!*object_2)
            {
                memcpy(command.object, object_1, BIG_LENGTH_WORD);
            }
            else if (!*object_3)
            {
                memcpy(command.object, object_1, BIG_LENGTH_WORD);
                strcat(command.object, " ");
                strcat(command.object, object_2);
            }
            else
            {
                memcpy(command.object, object_1, BIG_LENGTH_WORD);
                strcat(command.object, " ");
                strcat(command.object, object_2);
                strcat(command.object, " ");
                strcat(command.object, object_3);
            }
        }

        if (*target_1)
        {
            if (!*target_2)
            {
                memcpy(command.target, target_1, BIG_LENGTH_WORD);
            }
            else if (!*target_3)
            {
                memcpy(command.target, target_1, BIG_LENGTH_WORD);
                strcat(command.target, " ");
                strcat(command.target, target_2);
            }
            else
            {
                memcpy(command.target, target_1, BIG_LENGTH_WORD);
                strcat(command.target, " ");
                strcat(command.target, target_2);
                strcat(command.target, " ");
                strcat(command.target, target_3);
            }
        }
    }

    if (!parser[0])
    {
        display_commands();
    }
    else if (!strcmp(command.verb, "play"))
    {
        execute_play();
    }
    else if (!strcmp(command.verb, "inventory"))
    {
        execute_inventory();
    }
    else if (!strcmp(command.verb, "character"))
    {
        execute_character();
    }
    else if (!strcmp(command.verb, "go"))
    {
        execute_go();
    }
    else if (!strcmp(command.verb, "look"))
    {
        execute_look();
    }
    else if (!strcmp(command.verb, "take"))
    {
        execute_take();
    }
    else if (!strcmp(command.verb, "drop"))
    {
        execute_drop();
    }
    else if (!strcmp(command.verb, "use"))
    {
        execute_use();
    }
    else if (!strcmp(command.verb, "hold"))
    {
        execute_hold();
    }
    else
    {
        display_commands();
    }
    return;
}

