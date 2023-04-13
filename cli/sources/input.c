#include "../headers/input.h"
#include "../headers/output.h"

int input_yes_no(void)
{
    int i;
    char input[4] = {0};
    while (strcmp(input, "yes") && strcmp(input, "no"))
    {
        write_line("> ");
        if (fgets(input, 4, stdin))
        {
            for (i = 0; i < 4; ++i)
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
        write_line("\r");
    }
    return strcmp(input, "no");
}

/* ALREADY PRESENT IN THE "TWENTY SQUARES" LIBRARY
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
*/
