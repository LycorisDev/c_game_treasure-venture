#include "main.h"
#include "parser.h"
#include "start.h"

static int	output_int(int num, char *p_text, int index);

int	main(void)
{
	#ifdef _WIN32
	/* Terminal UTF8 encoding */
	SetConsoleOutputCP(CP_UTF8);
	#endif

	access_main_menu();
	while (1)
	{
		get_and_parse_input();
		interact();
	}

	return EXIT_SUCCESS;
}

void	add_output(const char *format, ...)
{
	int			i;
	int			j;
	int			max_len;
	char		*text;
	const char	*tmp;
	va_list		args;

	max_len = 509;
	text = calloc(max_len + 1, sizeof(char));
	tmp = 0;
	if (!text)
		return;

	va_start(args, format);

	for (i = 0, j = 0; i < max_len; ++i)
	{
		if (format[i] == '\0')
			break;

		/* Non-formatted */
		if (format[i] != '%')
		{
			text[j++] = format[i];
			continue;
		}

		++i;

		/* Percentage sign */
		if (format[i] == '%')
		{
			text[j++] = format[i];
		}
		/* String */
		else if (format[i] == 's')
		{
			tmp = va_arg(args, const char *);
			strncat(text, tmp, get_available_length_in_string(max_len, text));
			j += strlen(tmp);
		}
		/* Integer */
		else if (format[i] == 'd')
		{
			j = output_int(va_arg(args, int), text, j);
		}
	}

	va_end(args);
	write(STDOUT_FILENO, text, strlen(text));
	free(text);
	return;
}

void	reset_output(void)
{
	#ifdef _WIN32
	system("cls");
	#elif defined(__ANDROID__)
	system("clear");
	#else
	write(STDOUT_FILENO, "\033c", 2);
	#endif
	return;
}

void	close_window(void)
{
	reset_output();
	exit(EXIT_SUCCESS);
	return;
}

static int	output_int(int num, char *p_text, int index)
{
	int	a;

	if (num < 0)
	{
		p_text[index++] = '-';
		num *= -1;
	}

	if (num > 9)
	{
		a = num / 10;
		num -= 10 * a;
		index = output_int(a, p_text, index);
	}
	p_text[index++] = '0' + num;
	return index;
}
