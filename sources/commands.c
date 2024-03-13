#include "../headers/commands.h"
#include "../headers/parser.h"
#include "../headers/play.h"
#include "../headers/inventory.h"
#include "../headers/go.h"
#include "../headers/look.h"
#include "../headers/take.h"
#include "../headers/drop.h"
#include "../headers/use.h"

/* Declared as extern in ../headers/commands.h */
Command command;

static const KeyFunc command_list[] = 
{
    {"drop", &execute_drop},
    {"go", &execute_go},
    {"inventory", &execute_inventory},
    {"look", &execute_look},
    {"play", &execute_play},
    {"take", &execute_take},
    {"use", &execute_use},
    {NULL, &display_game_commands}
};

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
    add_output("\t['Menu']    ['Inventory']    ['Look']    ['Take']\n");
    add_output("\t['Play']       ['Use']        ['Go']     ['Drop']\n");
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
    int i = 0;
    while (command_list[i].key != NULL)
    {
        if (!strcmp(command.verb, command_list[i].key))
        {
            command_list[i].func();
            return;
        }
        ++i;
    }

    command_list[i].func();
    return;
}

