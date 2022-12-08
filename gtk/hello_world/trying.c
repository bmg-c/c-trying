#include <gtk/gtk.h>
typedef struct {
    char *this;
    char *that;
} example;

void callback_func (GtkWidget *ignored, example *test) {
    printf("%s and %s\n",test->this, test->that);
}


// int main(int argc, char *argv[]) {
//     char this[]="this", that[]="that";
//     example test;
//     GtkWidget *window, *button;

//     test.this=this;
//     test.that=that;

//     window = gtk_window_new ();
//     // gtk_window_set_default_size (GTK_WINDOW (window), 1000, 1000);


//     button = gtk_button_new_with_label ("click here");
//     gtk_window_set_child (GTK_WINDOW (window), button);
//     g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_func), (gpointer*)&test);

//     gtk_widget_show(window);
//     return 0;
// }
static void activate (GtkApplication *app, gpointer user_data) { // Окно
    char this[]="this", that[]="that";
    example test;
    GtkWidget *window, *button;

    test.this=this;
    test.that=that;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Окно"); // Название окна
    gtk_window_set_default_size (GTK_WINDOW (window), 1000, 1000); // Размер окна

    button = gtk_button_new_with_label ("Сгенерировать массив");
    gtk_window_set_child (GTK_WINDOW (window), button);

    // g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_func), (gpointer*)&test);

    gtk_widget_show (window); // Показать окно
}

int main (int argc, char **argv) { // Ее смысл - вызвать объект GtkApplication 
    GtkApplication *app;
    app = gtk_application_new ("org.gtk.hello", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    g_object_unref (app);

    return 0;
}
