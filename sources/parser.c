#include "../headers/parser.h"
#include "../headers/output.h"

char parser[PARSER_NBR_WORDS][LENGTH_WORD];
int nbr_words_in_parser;
yes_no_callback_t yes_no_callback = NULL;

static void reset_parser(void);
static void str_to_lowercase(char dest[], const char* src);
static void fill_parser(char input[]);

void parse_input(const char* raw_input)
{
    char input[INPUT_MAX_LENGTH] = {0};

    reset_parser();

    if (strlen(raw_input) == 0)
        return;

    str_to_lowercase(input, raw_input);
    fill_parser(input);
    return;
}

#ifdef CLI
void get_and_parse_cli_input(void)
{
    char input[INPUT_MAX_LENGTH] = {0};
    char c = 'A';

    /* Get input from stdin */
    f_write_line(stdout, "\n");
    f_write_line(stdout, "> ");
    if (fgets(input, INPUT_MAX_LENGTH, stdin))
    {
        if (input[0] == '\n')
            return;
        /* Parse here */
        parse_input(input);
    }
    f_write_line(stdout, "\n");

    /* Flush stdin */
    if (!fseek(stdin, 0, SEEK_END))
    {
        while (c != '\n' && c != EOF)
            c = getchar();
    }
    return;
}
#endif

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
    for (i = 0; i < INPUT_MAX_LENGTH; ++i)
    {
        if (src[i] == '\0')
            break;
        dest[i] = tolower(src[i]);
    }
    return;
}

static void fill_parser(char input[])
{
    char *token = strtok(input, INPUT_TOKEN_DELIMETERS);
    while (token)
    {
        strcpy(parser[nbr_words_in_parser++], token);
        token = strtok(NULL, INPUT_TOKEN_DELIMETERS);
    }
    return;
}

