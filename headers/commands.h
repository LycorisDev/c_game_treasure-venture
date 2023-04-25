#ifndef COMMANDS_H
#define COMMANDS_H

#ifndef STANDARD_LIBRARY_STDIO
#define STANDARD_LIBRARY_STDIO
#include <stdio.h>
#endif
#ifndef STANDARD_LIBRARY_STDLIB
#define STANDARD_LIBRARY_STDLIB
#include <stdlib.h>
#endif
#ifndef STANDARD_LIBRARY_STRING
#define STANDARD_LIBRARY_STRING
#include <string.h>
#endif

#include "lexicon.h"

#define BIG_LENGTH_WORD (LENGTH_WORD * 3 + 2)

typedef struct command
{
    char verb[LENGTH_WORD];
    char object[BIG_LENGTH_WORD];
    char preposition[LENGTH_WORD];
    char target[BIG_LENGTH_WORD];
} Command;

extern Command command;

void execute_game_command(void);
void display_game_commands(void);

#endif

