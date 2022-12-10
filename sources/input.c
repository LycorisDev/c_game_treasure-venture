#include "../headers/input.h"

void get_string_input(char* input, const char context[], const char question[], const char choices[])
{
    int i;
    if (!strcmp(context, "yes_no"))
    {
        printf("%s %s\n\n", question, choices);

        while (strcmp(input, "yes") && strcmp(input, "no"))
        {
            printf("> ");
            if (fgets(input, INPUT_SIZE, stdin))
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
            }
            flush_stdin();
            only_one_greaterthan_sign_is_printed();
        }
    }
    return;
}

int get_number_input(const int min_number, const int max_number, const char question[])
{
    char input[8] = {0};
    int number = 0;

    printf("%s %d - %d.\n\n", question, min_number, max_number);

    while (number < min_number || number > max_number)
    {
        printf("> ");
        if (fgets(input, 8, stdin))
            number = atoi(input);
        flush_stdin();
        only_one_greaterthan_sign_is_printed();
    }

    printf("\n");
    return number;
}

/* When passed to a function, the array decays to a pointer to the first element, so you must compute array_count before it decays:
    array_count = sizeof(number_array)/sizeof(number_array[0]) */
int get_number_input_amongst_array(const int number_array[], const int array_count, const char question[])
{
    char input[8] = {0};
    int i, number = 0, is_number_valid = 0;

    printf("%s\n", question);
    for (i = 0; i < array_count; ++i)
    {
        if (i == array_count - 1)
            printf("%d.\n\n", number_array[i]);
        else
            printf("%d - ", number_array[i]);
    }

    while (!is_number_valid)
    {
        printf("> ");
        if (fgets(input, 8, stdin))
        {
            number = atoi(input);
            for (i = 0; i < array_count; ++i)
            {
                if (number == number_array[i])
                {
                    is_number_valid = 1;
                    break;
                }
            }
        }
        flush_stdin();
        only_one_greaterthan_sign_is_printed();
    }

    printf("\n");
    return number;
}

void flush_stdin(void)
{
    char c = 'A';
    if (!fseek(stdin, 0, SEEK_END))
    {
        while (c != '\n' && c != EOF)
            c = getchar();
    }
    return;
}

void only_one_greaterthan_sign_is_printed(void)
{
    printf("\r");
    return;
}

void press_enter_to_continue(void)
{
    char c = '\0';
    printf("Press ENTER to continue.\n");
    printf("> ");
    while (c != '\n')
    {
        c = getchar();
    }
    flush_stdin();
    return;
}

void clear_terminal(void)
{
    printf("\033c");
    return;
}

