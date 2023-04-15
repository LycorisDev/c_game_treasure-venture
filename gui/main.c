#include <gtk/gtk.h>

/*
    gcc `pkg-config --cflags gtk4` main.c -o builds/gtk/gtk-test `pkg-config --libs gtk4`
*/

static void on_close_button_clicked(GtkWidget* btn, GtkWidget* window)
{
    gtk_window_close(GTK_WINDOW(window));
    return;
}

static gboolean is_window_maximized = FALSE;
static void on_maximize_button_clicked(GtkWidget* btn, GtkWidget* window)
{
    if (is_window_maximized)
    {
        gtk_window_unmaximize(GTK_WINDOW(window));
        is_window_maximized = FALSE;
    }
    else
    {
        gtk_window_maximize(GTK_WINDOW(window));
        is_window_maximized = TRUE;
    }
    return;
}

static void on_minimize_button_clicked(GtkWidget* btn, GtkWidget* window)
{
    gtk_window_minimize(GTK_WINDOW(window));
    return;
}

static void on_text_input_sent(GtkEntry* input_field, GtkTextBuffer* output_buffer)
{
    const char* text = gtk_editable_get_text(GTK_EDITABLE(input_field));
    gtk_text_buffer_insert_at_cursor(output_buffer, text, -1);
    gtk_editable_set_text(GTK_EDITABLE(input_field), "\0");
    return;
}

static void on_app_activated(GApplication* app, gpointer user_data)
{
    char* app_name = (char*)user_data;
    GtkWidget *window, *title_bar, *close_button, *maximize_button, *minimize_button;
    GtkWidget *box, *output_area, *input_field;
    GtkTextBuffer* output_buffer;

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
    g_signal_connect(close_button, "clicked", G_CALLBACK(on_close_button_clicked), window);

    maximize_button = gtk_button_new_from_icon_name("window-maximize");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(title_bar), maximize_button);
    g_signal_connect(maximize_button, "clicked", G_CALLBACK(on_maximize_button_clicked), window);

    minimize_button = gtk_button_new_from_icon_name("window-minimize");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(title_bar), minimize_button);
    g_signal_connect(minimize_button, "clicked", G_CALLBACK(on_minimize_button_clicked), window);

    /* Container */
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(window), box);

    /* Children of the container */
    output_area = gtk_text_view_new();
    gtk_widget_set_hexpand(output_area, TRUE);
    gtk_widget_set_vexpand(output_area, TRUE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(output_area), FALSE);
    output_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_area));
    gtk_text_buffer_set_text(output_buffer, "This is the output.\nLine 2.\nLine 3.", -1);
    gtk_box_append(GTK_BOX(box), output_area);

    input_field = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(input_field), "Type here...");
    gtk_box_append(GTK_BOX(box), input_field);
    g_signal_connect(input_field, "activate", G_CALLBACK(on_text_input_sent), output_buffer);

    /* Put the focus in the input field */
    gtk_widget_grab_focus(input_field);

    /* Present the window */
    gtk_window_present(GTK_WINDOW(window));

    g_print("The \"%s\" GtkApplication is activated.\n", app_name);
    return;
}

int main(int argc, char* argv[])
{
    GtkApplication* app;
    int status;
    char app_name[] = "Treasure Venture";

    /* Init */
    app = gtk_application_new("com.mofumofustudios.treasure_venture", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_app_activated), app_name);

    /* Run */
    status = g_application_run(G_APPLICATION(app), argc, argv);

    /* Clean */
    g_object_unref(app);
    return status;
}

