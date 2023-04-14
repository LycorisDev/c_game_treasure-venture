#include <gtk/gtk.h>

/*
    gcc `pkg-config --cflags gtk4` main.c -o builds/gtk/gtk-test `pkg-config --libs gtk4`
*/

static void app_activate(GApplication* app, gpointer user_data)
{
    char* app_name = (char*)user_data;
    GtkWidget* window;

    /*
        Create a window and connect it to the app:
        When the window is closed, the app terminates too.
        If the app is not linked to a window, it has nothing to wait for and terminates immediately.
    */
    window = gtk_application_window_new(GTK_APPLICATION(app));

    /* Set the window's properties */
    gtk_window_set_title(GTK_WINDOW(window), app_name);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

    /*
        Present the window: 
        Display the window if it wasn't already displayed + Place it above all the other windows of this app.
    */
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
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), app_name);

    /* Run */
    status = g_application_run(G_APPLICATION(app), argc, argv);

    /* Clean */
    g_object_unref(app);
    return status;
}

