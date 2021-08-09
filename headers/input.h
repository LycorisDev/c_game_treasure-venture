#ifndef INPUT_H
#define INPUT_H

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
#ifndef STANDARD_LIBRARY_CTYPE
#define STANDARD_LIBRARY_CTYPE
#include <ctype.h>
#endif

void get_string_input(char* input, const char context[], const char question[], const char choices[]);
int get_number_input(const int min_number, const int max_number, const char question[]);
int get_number_input_amongst_array(const int number_array[], const int array_count, const char question[]);
void flush_stdin(void);
void only_one_greaterthan_sign_is_printed(void);
void press_enter_to_continue(void);
void clear_terminal(void);

#define INPUT_SIZE    40

#endif

