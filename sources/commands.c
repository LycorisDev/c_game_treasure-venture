#include "../headers/commands.h"
#include "../headers/parser.h"

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

static void reset_command_elements(void);
static void set_command_element(void* element, const int element_size, const int parser_start_index, const int parser_end_index);
static void execute_action(void);

void execute_game_command(void)
{
    int i;
    int command_word_length = nbr_words_in_parser;
    int verb_index = 0, object_end_index = -1, preposition_index = -1, target_start_index = -1;

    reset_command_elements();

    for (i = 0; i < nbr_words_in_parser; ++i)
    {
        if (!bool_word_is_in_lexicon(parser[i]))
        {
            add_output("\t['%s' was not recognized.]\n\n", parser[i]);
            command_word_length = i;
            break;
        }

        if (preposition_index != -1)
            continue;

        object_end_index = i;

        if (bool_word_is_preposition(parser[i]))
        {
            object_end_index = i - 1;
            preposition_index = i;
            target_start_index = i + 1;
        }
    }

    if (!command_word_length)
    {
        display_game_commands();
        return;
    }

    set_command_element(command.verb, sizeof(command.verb), verb_index, verb_index);
    set_command_element(command.object, sizeof(command.object), verb_index + 1, object_end_index);
    set_command_element(command.preposition, sizeof(command.preposition), preposition_index, preposition_index);
    set_command_element(command.target, sizeof(command.target), target_start_index, command_word_length - 1);

    execute_action();
    return;
}

void display_game_commands(void)
{
    add_output("\t['Menu']    ['Inventory']    ['Go']      ['Take']    ['Use']\n");
    add_output("\t['Play']    ['Character']    ['Look']    ['Drop']    ['Hold']\n");
    add_output("\n");
    return;
}

static void reset_command_elements(void)
{
    memset(&command, 0, sizeof(command));
    return;
}

static void set_command_element(void* element, const int element_size, const int parser_start_index, const int parser_end_index)
{
    int i = parser_start_index;
    const int max_len = element_size - 1;

    if (parser_start_index > parser_end_index || parser_start_index == -1 || parser_end_index == -1)
        return;

    memcpy(element, parser[i++], max_len);

    while (i <= parser_end_index)
    {
        strncat(element, " ", get_available_length_in_string(max_len, element));
        strncat(element, parser[i++], get_available_length_in_string(max_len, element));
    }
    return;
}

static void execute_action(void)
{
    if (!strcmp(command.verb, "play"))
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
        display_game_commands();
    }
}

