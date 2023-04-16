#include <gtk/gtk.h>
#include "../headers/main.h"
#include "../headers/start.h"

char* parser[MAX_NBR_WORDS];
int nbr_words_in_parser;

static GtkWidget* window = NULL;
static GtkTextBuffer* output_buffer = NULL;
static gboolean is_window_maximized = FALSE;

static void on_app_activated(GApplication* app, gpointer user_data);
static void on_minimize_button_clicked(GtkWidget* btn);
static void on_maximize_button_clicked(GtkWidget* btn);
static void on_close_button_clicked(GtkWidget* btn);
static void on_text_input_sent(GtkEntry* input_field);
static void parse_input(const char* raw_input);
static int output_int(int num, char* p_text, int index);

int main(int argc, char* argv[])
{
    GtkApplication* app;
    int status;
    char app_name[] = "Treasure Venture";

    app = gtk_application_new("com.mofumofustudios.treasure_venture", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_app_activated), app_name);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

void add_output(const char* format, ...)
{
    int i, j;
    int max_len = 509;
    char* text = calloc(max_len + 1, sizeof(char));
    const char* tmp = NULL;
    va_list args;

    if (text == NULL)
        return;

    va_start(args, format);

    for (i = 0, j = 0; i < max_len; ++i)
    {
        if (format[i] == '\0')
            break;

        if (format[i] != '%')
            text[j++] = format[i];
        else
        {
            ++i;

            if (format[i] == '%')
            {
                text[j++] = format[i];
            }
            else if (format[i] == 's')
            {
                tmp = va_arg(args, const char*);
                strcat(text, tmp);
                j += strlen(tmp);
            }
            else if (format[i] == 'd')
            {
               j = output_int(va_arg(args, int), text, j);
            }
        }
    }

    va_end(args);

    gtk_text_buffer_insert_at_cursor(output_buffer, text, -1);
    free(text);
    return;
}

void reset_output(void)
{
    gtk_text_buffer_set_text(output_buffer, "", -1);
}

void close_window(void)
{
    gtk_window_close(GTK_WINDOW(window));
    return;
}

static void on_app_activated(GApplication* app, gpointer user_data)
{
    char* app_name = (char*)user_data;
    GtkWidget *title_bar, *close_button, *maximize_button, *minimize_button;
    GtkWidget *box, *output_area, *input_field;

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
    g_signal_connect(close_button, "clicked", G_CALLBACK(on_close_button_clicked), NULL);

    maximize_button = gtk_button_new_from_icon_name("window-maximize");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(title_bar), maximize_button);
    g_signal_connect(maximize_button, "clicked", G_CALLBACK(on_maximize_button_clicked), NULL);

    minimize_button = gtk_button_new_from_icon_name("window-minimize");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(title_bar), minimize_button);
    g_signal_connect(minimize_button, "clicked", G_CALLBACK(on_minimize_button_clicked), NULL);

    /* Container */
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(window), box);

    /* Children of the container */
    output_area = gtk_text_view_new();
    gtk_widget_set_hexpand(output_area, TRUE);
    gtk_widget_set_vexpand(output_area, TRUE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(output_area), FALSE);
    output_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_area));
    gtk_text_buffer_set_text(output_buffer, "", -1);
    gtk_box_append(GTK_BOX(box), output_area);

    input_field = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(input_field), "Type here...");
    gtk_box_append(GTK_BOX(box), input_field);
    g_signal_connect(input_field, "activate", G_CALLBACK(on_text_input_sent), NULL);

    /* Put the focus in the input field */
    gtk_widget_grab_focus(input_field);

    /* Present the window */
    gtk_window_present(GTK_WINDOW(window));

    /* Start the game */
    return;
}

static void on_minimize_button_clicked(GtkWidget* btn)
{
    gtk_window_minimize(GTK_WINDOW(window));
    return;
}

static void on_maximize_button_clicked(GtkWidget* btn)
{
    if (is_window_maximized)
        gtk_window_unmaximize(GTK_WINDOW(window));
    else
        gtk_window_maximize(GTK_WINDOW(window));
    is_window_maximized = !is_window_maximized;
    return;
}

static void on_close_button_clicked(GtkWidget* btn)
{
    close_window();
    return;
}

static void on_text_input_sent(GtkEntry* input_field)
{
    const char* text = gtk_editable_get_text(GTK_EDITABLE(input_field));
    if (strlen(text) != 0)
    {
        parse_input(text);
        gtk_editable_set_text(GTK_EDITABLE(input_field), "\0");
        /* interact(); */
    }
    return;
}

static void parse_input(const char* raw_input)
{
    int i;
    char *token = NULL;
    char input[MAX_SIZE] = {0};

    /* Reset parser */
    memset(parser, 0, sizeof(parser));
    nbr_words_in_parser = 0;

    /* Set input to lowercase */
    for (i = 0; i < MAX_SIZE; ++i)
    {
        if (raw_input[i] == '\0')
            break;
        input[i] = tolower(raw_input[i]);
    }

    /* Fill parser */
    token = strtok(input, DELIMETERS);
    while (token)
    {
        parser[nbr_words_in_parser++] = token;
        token = strtok(NULL, DELIMETERS);
    }
    return;
}

static int output_int(int num, char* p_text, int index)
{
    int a;

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

