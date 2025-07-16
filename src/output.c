#include "output.h"

static void	f_write_int(FILE *stream, int num);

void	f_write_line(FILE *stream, const char *format, ...)
{
	int		i;
	va_list	args;

	i = 0;
	va_start(args, format);

	while (format[i] != '\0')
	{
		/* Non-formatted */
		if (format[i] != '%')
		{
			fputc(format[i], stream);
			++i;
			continue;
		}

		++i;

		/* Percentage sign */
		if (format[i] == '%')
		{
			fputc(format[i], stream);
		}
		/* String */
		else if (format[i] == 's')
		{
			fputs(va_arg(args, const char*), stream);
		}
		/* Integer */
		else if (format[i] == 'd')
		{
			f_write_int(stream, va_arg(args, int));
		}

		++i;
	}

	va_end(args);
	return;
}

static void	f_write_int(FILE *stream, int num)
{
	int	a;

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
