#include "../headers/save.h"

static void f_write_line(FILE* stream, const char* format, ...);
static void f_write_int(FILE* stream, int num);

void save_game(FILE* save_file)
{
    int i;

    f_write_line(save_file, "previous_location:%d\n", !PLAYER->previous_location ? -1 : PLAYER->previous_location->id);
    f_write_line(save_file, "current_location:%d\n", PLAYER->current_location->id);

    f_write_line(save_file, "events:");
    for (i = 0; i < NBR_EVENTS; ++i)
    {
        if (!i)
            f_write_line(save_file, "%d", list_events[i]);
        else
            f_write_line(save_file, ",%d", list_events[i]);
    }
    f_write_line(save_file, "\n");

    f_write_line(save_file, "inventory:");
    for (i = 0; i < NBR_ITEMS; ++i)
    {
        if (!PLAYER->inventory[i])
            break;

        if (!i)
            f_write_line(save_file, "%d", PLAYER->inventory[i]->id);
        else
            f_write_line(save_file, ",%d", PLAYER->inventory[i]->id);
    }
    f_write_line(save_file, "\n");

    return;
}

static void f_write_line(FILE* stream, const char* format, ...)
{
    int i = 0;
    va_list args;

    va_start(args, format);

    while (format[i] != '\0')
    {
        if (format[i] == '%')
        {
            ++i;
            if (format[i] == 'd')
            {
                f_write_int(stream, va_arg(args, int));
            }
            else if (format[i] == 's')
            {
                fputs(va_arg(args, const char*), stream);
            }
            else if (format[i] == '%')
            {
                fputc(format[i], stream);
            }
        }
        else
            fputc(format[i], stream);

        ++i;
    }

    va_end(args);
    return;
}

static void f_write_int(FILE* stream, int num)
{
    int a;

    if (num < 0)
    {
        fputc('-', stream);
        num *= -1;
    }

    if (num > 9)
    {
        a = num / 10;
        num -= 10 * a;
        f_write_int(stream, a);
    }
    fputc('0' + num, stream);
    return;
}

