#ifdef GUI
#include <gtk/gtk.h>
#endif
#include "main.h"
#include "parser.h"
#include "start.h"

#ifdef GUI
static GtkWidget		*window = 0;
static GtkWidget		*output_area = 0;
static GtkCssProvider	*css_provider = 0;
static GtkTextBuffer	*output_buffer = 0;
static gboolean			is_window_maximized = FALSE;

static void	on_app_activated(GApplication *app, gpointer user_data);
static void	on_minimize_button_clicked(void);
static void	on_maximize_button_clicked(void);
static void	on_close_button_clicked(void);
static void	on_text_input_sent(GtkEntry *input_field);
static void	scroll_to_bottom(void);
#endif
static int	output_int(int num, char *p_text, int index);

#ifdef GUI
int	main(int argc, char **argv)
{
	int				status;
	char			*app_name;
	GtkApplication	*app;

	status = EXIT_SUCCESS;
	app_name = "Treasure Venture";
	app = gtk_application_new("com.lycorisdev.treasure_venture", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(on_app_activated), app_name);

	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(css_provider);
	g_object_unref(app);
	return status;
}
#else
int	main(void)
{
	#ifdef _WIN32
	/* Terminal UTF8 encoding */
	SetConsoleOutputCP(CP_UTF8);
	#endif

	access_main_menu();
	while (1)
	{
		get_and_parse_cli_input();
		interact();
	}

	return EXIT_SUCCESS;
}
#endif

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

	#ifdef GUI
	gtk_text_buffer_insert_at_cursor(output_buffer, text, -1);
	scroll_to_bottom();
	#else
	write(STDOUT_FILENO, text, strlen(text));
	#endif

	free(text);
	return;
}

void	reset_output(void)
{
	#ifdef GUI
	gtk_text_buffer_set_text(output_buffer, "", -1);
	#else
	# ifdef _WIN32
	system("cls");
	# elif defined(__ANDROID__)
	system("clear");
	# else
	write(STDOUT_FILENO, "\033c", 2);
	# endif
	#endif
	return;
}

void	close_window(void)
{
	#ifdef GUI
	gtk_window_close(GTK_WINDOW(window));
	#else
	reset_output();
	exit(EXIT_SUCCESS);
	#endif
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

#ifdef GUI
static void	on_app_activated(GApplication *app, gpointer user_data)
{
	char			*app_name;
	GtkWidget		*title_bar;
	GtkWidget		*close_button;
	GtkWidget		*maximize_button;
	GtkWidget		*minimize_button;
	GtkWidget		*box;
	GtkWidget		*scrolled_window;
	GtkWidget		*input_field;
	GtkStyleContext	*style_context_output_area;

	app_name = (char *)user_data;

	/* CSS provider */
	css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_data(css_provider, "textview { padding: 10px; }\n", -1);

	/* Window */
	window = gtk_application_window_new(GTK_APPLICATION(app));
	gtk_window_set_title(GTK_WINDOW(window), app_name);
	gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

	/* Title bar */
	title_bar = gtk_header_bar_new();
	gtk_window_set_titlebar(GTK_WINDOW(window), title_bar);
	gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(title_bar), FALSE);

	/* Title bar buttons */
	close_button = gtk_button_new_from_icon_name("window-close");
	gtk_header_bar_pack_end(GTK_HEADER_BAR(title_bar), close_button);
	g_signal_connect(close_button, "clicked", G_CALLBACK(on_close_button_clicked), 0);

	maximize_button = gtk_button_new_from_icon_name("window-maximize");
	gtk_header_bar_pack_end(GTK_HEADER_BAR(title_bar), maximize_button);
	g_signal_connect(maximize_button, "clicked", G_CALLBACK(on_maximize_button_clicked), 0);

	minimize_button = gtk_button_new_from_icon_name("window-minimize");
	gtk_header_bar_pack_end(GTK_HEADER_BAR(title_bar), minimize_button);
	g_signal_connect(minimize_button, "clicked", G_CALLBACK(on_minimize_button_clicked), 0);

	/* Container */
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_window_set_child(GTK_WINDOW(window), box);

	/* Children of the container */
	output_area = gtk_text_view_new();
	gtk_widget_set_hexpand(output_area, TRUE);
	gtk_widget_set_vexpand(output_area, TRUE);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(output_area), FALSE);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(output_area), FALSE);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(output_area), GTK_WRAP_WORD_CHAR);
	gtk_text_view_set_justification(GTK_TEXT_VIEW(output_area), GTK_JUSTIFY_FILL);
	output_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_area));
	gtk_text_buffer_set_text(output_buffer, "", -1);

	style_context_output_area = gtk_widget_get_style_context(output_area);
	gtk_style_context_add_provider(style_context_output_area, 
			GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	scrolled_window = gtk_scrolled_window_new();
	gtk_widget_set_vexpand(scrolled_window, TRUE);
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), output_area);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	gtk_box_append(GTK_BOX(box), scrolled_window);

	input_field = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(input_field), "Type here...");
	gtk_box_append(GTK_BOX(box), input_field);
	g_signal_connect(input_field, "activate", G_CALLBACK(on_text_input_sent), 0);

	/* Put the focus in the input field */
	gtk_widget_grab_focus(input_field);

	/* Present the window */
	gtk_window_present(GTK_WINDOW(window));

	/* Start the game */
	access_main_menu();
	return;
}

static void	on_minimize_button_clicked(void)
{
	gtk_window_minimize(GTK_WINDOW(window));
	return;
}

static void	on_maximize_button_clicked(void)
{
	if (is_window_maximized)
		gtk_window_unmaximize(GTK_WINDOW(window));
	else
		gtk_window_maximize(GTK_WINDOW(window));
	is_window_maximized = !is_window_maximized;
	return;
}

static void	on_close_button_clicked(void)
{
	close_window();
	return;
}

static void	on_text_input_sent(GtkEntry *input_field)
{
	const char	*text;

	text = gtk_editable_get_text(GTK_EDITABLE(input_field));
	parse_input(text);
	gtk_editable_set_text(GTK_EDITABLE(input_field), "\0");
	interact();
	return;
}

static void	scroll_to_bottom(void)
{
	GtkTextIter	end_iter;
	GtkTextMark	*end_mark;

	gtk_text_buffer_get_end_iter(output_buffer, &end_iter);
	end_mark = gtk_text_buffer_create_mark(output_buffer, "end", &end_iter, FALSE);
	gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW(output_area), end_mark);
	gtk_text_buffer_delete_mark(output_buffer, end_mark);
	return;
}
#endif
