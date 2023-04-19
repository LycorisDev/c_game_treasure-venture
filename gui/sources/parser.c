#include "../headers/parser.h"

char parser[MAX_NBR_WORDS][BIG_LENGTH_WORD];
int nbr_words_in_parser;
yes_no_callback_t yes_no_callback = NULL;

static void reset_parser(void);
static void str_to_lowercase(char dest[], const char* src);
static void fill_parser(char input[]);

void parse_input(const char* raw_input)
{
    char input[MAX_SIZE] = {0};

    reset_parser();

    if (strlen(raw_input) == 0)
        return;

    str_to_lowercase(input, raw_input);
    fill_parser(input);
    return;
}

void parse_yes_no(void)
{
    if (parser[0])
    {
        if (!strcmp(parser[0], "yes"))
        {
            yes_no_callback(1);
            yes_no_callback = NULL;
        }
        else if (!strcmp(parser[0], "no"))
        {
            yes_no_callback(0);
            yes_no_callback = NULL;
        }
    }
    return;
}

static void reset_parser(void)
{
    memset(parser, 0, sizeof(parser));
    nbr_words_in_parser = 0;
    return;
}

static void str_to_lowercase(char dest[], const char* src)
{
    int i;
    for (i = 0; i < MAX_SIZE; ++i)
    {
        if (src[i] == '\0')
            break;
        dest[i] = tolower(src[i]);
    }
    return;
}

static void fill_parser(char input[])
{
    char *token = strtok(input, DELIMETERS);
    while (token)
    {
        strcpy(parser[nbr_words_in_parser++], token);
        token = strtok(NULL, DELIMETERS);
    }
    return;
}

