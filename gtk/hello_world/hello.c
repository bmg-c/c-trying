// https://docs.gtk.org/gtk4/getting_started.html#building-applications

#include <gtk/gtk.h>
#include "lab6.h"

struct MyWidgets {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *button;
    GtkWidget *input_size;
    GtkWidget *size;
    GtkWidget *input_text;
    GtkWidget *text;
    GtkWidget *box_text;
};

// void func1 (GtkWidget *ignored, gpointer data) {
//     g_print ("%s", gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (((GtkWidget *) data)->text)));
//     // g_print ("%s", gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (widgets->buffer)));
// }

static void activate (GtkApplication *app, gpointer user_data) { // Окно
    // Создаем виджеты, т.е указатели типа GtkWidget
    struct MyWidgets widgets;
    // Создает GtkApplicationWindow и сохранит его в window
    widgets.window = gtk_application_window_new (app);

    int *widgets_addr = &widgets;


    /*
     * gtk_window_set_title() принимает указатели GtkWindow, а не GtkWidget.
     *
     * Поэтому нам следует перевести наш window в тип GtkWindow, и вместо того,
     * чтобы делать это через стандартный переводчик Си ((GtkWindow *) window),
     * мы используем макрос GTK_WINDOW(), который производит проверку
     * является ли указатель инстанцией GtkWindow
     */
    gtk_window_set_title (GTK_WINDOW (widgets.window), "Окно"); // Название окна
    gtk_window_set_default_size (GTK_WINDOW (widgets.window), 1000, 1000); // Размер окна

    widgets.box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign (widgets.box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (widgets.box, GTK_ALIGN_END);

    gtk_window_set_child (GTK_WINDOW (widgets.window), widgets.box);

    widgets.button = gtk_button_new_with_label ("Сгенерировать массив");
    gtk_box_append (GTK_BOX (widgets.box), widgets.button);

    widgets.input_size = gtk_entry_new ();
    widgets.size = gtk_entry_buffer_new (NULL, 0);
    gtk_entry_set_buffer (GTK_ENTRY (widgets.input_size), GTK_ENTRY_BUFFER (widgets.size));
    gtk_entry_set_placeholder_text (GTK_ENTRY (widgets.input_size), "Размерность массива");
    gtk_box_append (GTK_BOX (widgets.box), widgets.input_size);

    widgets.input_text = gtk_entry_new ();
    widgets.text = gtk_entry_buffer_new (NULL, 0);
    gtk_widget_set_size_request (widgets.input_text, 1000, 800);
    gtk_entry_set_buffer (GTK_ENTRY (widgets.input_text), GTK_ENTRY_BUFFER (widgets.text));
    gtk_entry_set_placeholder_text (GTK_ENTRY (widgets.input_text), "Здесь будет вывод программы");
    gtk_box_prepend (GTK_BOX (widgets.box), widgets.input_text);

    g_signal_connect (widgets.button, "clicked", G_CALLBACK (func), widgets.text);

    gtk_widget_show (widgets.window); // Показать окно
}

int main (int argc, char **argv) { // Ее смысл - вызвать объект GtkApplication 
    GtkApplication *app; // Создаем объект GtkApplication
    int status;

    /*
     * Когда мы создаем GtkApplication ей нужен identifier, а также - флаги.
     * Эти флаги указывают на то, какие возможности имеет приложение.
     */
    app = gtk_application_new ("org.gtk.hello", G_APPLICATION_DEFAULT_FLAGS);

    // Подключаем сигнал активации к active()
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    /*
     * Сигнал активности будет отправлен, когда приложение запускается через
     * g_application_run, где мы для начала указываем какое приложение, а
     * после она может принимать аргументы, написанные через коммандную строку.
     * 
     * Внутри g_application_run сигнал activate() отправляется и мы проходим в
     * функцию activate().
     */  
    status = g_application_run (G_APPLICATION (app), argc, argv);

    /*
     * Когда выходим из окна - освобождаем объект GtkApplication из памяти.
     */
    g_object_unref (app);

    g_print ("%d", status); // 0 - если верно
    return status; // Возвращаем статус системе
}
