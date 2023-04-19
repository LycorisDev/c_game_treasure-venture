#include "../headers/output.h"

static void write_int(int num)
{
    int a;

    if (num < 0)
    {
        putchar('-');
        num *= -1;
    }

    if (num > 9)
    {
        a = num / 10;
        num -= 10 * a;
        write_int(a);
    }
    putchar('0' + num);
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

/* Needed format: %d and %s + '%' */
void write_line(const char* format, ...)
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
                write_int(va_arg(args, int));
            }
            else if (format[i] == 's')
            {
                fputs(va_arg(args, const char*), stdout);
            }
            else if (format[i] == '%')
            {
                putchar(format[i]);
            }
        }
        else
            putchar(format[i]);

        ++i;
    }

    va_end(args);
    return;
}

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

