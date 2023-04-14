#include <gtk/gtk.h>

/*
    gcc `pkg-config --cflags gtk4` main.c -o builds/gtk/gtk-test `pkg-config --libs gtk4`
*/

static void app_activate(GApplication* app, gpointer user_data)
{
    g_print("The \"%s\" GtkApplication is activated.\n", (char*)user_data);
    return;
}

int main(int argc, char *argv[])
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

