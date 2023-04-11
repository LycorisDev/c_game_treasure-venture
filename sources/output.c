#include "../headers/output.h"

void write_int(int num)
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

