#include "../headers/output.h"

static void f_write_int(FILE* stream, int num);

/* Needed format: %d and %s + '%' */
void f_write_line(FILE* stream, const char* format, ...)
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

