//GTK interface

//#include <stdlib.h>
#include <gtk/gtk.h>

char *image_file_path = NULL;

// Make objects global variables
GtkBuilder *builder;
GtkWidget *window;
GtkWidget *fixed;
GtkWidget *label_title;
GtkWidget *button_import;
GtkWidget *label_import;
GtkWidget *image;

int main(int argc, char *argv[]) 
{
    //Initialize GTK with arguments
    gtk_init(&argc, &argv);
    
    //Reads the XML glade file
    builder = gtk_builder_new_from_file("interface.glade");
    
    //Builds the GTK window
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    
    //Destroys program on application exit
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //Builds a table to see where does the signals come from
    gtk_builder_connect_signals(builder, NULL);
    
    //Pointers for GTK objects
    fixed= GTK_WIDGET(gtk_builder_get_object(builder,"fixed"));
    button_import= GTK_WIDGET(gtk_builder_get_object(builder,"button_import"));
    label_import= GTK_WIDGET(gtk_builder_get_object(builder, "label_import"));
    label_title= GTK_WIDGET(gtk_builder_get_object(builder, "label_title"));
    image= GTK_WIDGET(gtk_builder_get_object(builder,"image"));

    gtk_widget_show(window);
    gtk_main();
    return EXIT_SUCCESS;
}

/*
void on_button_import_clicked(GtkButton *b)
{
    gtk_label_set_text(GTK_LABEL(label_import),(const gchar*)
    "Import image from device files");
    
    //GtkWidget *dialog;
    //dialog = gtk_file_chooser_dialog_new("Import image from device files", GTK_WINDOW(window),
    //GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    //gtk_widget_show_all(dialog);
    //gint resp = 
    
    
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(button_import);
    gchar *filename = gtk_file_chooser_get_filename(chooser);
    
    //gchar *filename = gtk_file_chooser_get_filename(button_import("Import image from device files"));
    //gchar *filename = gtk_file_chooser_get_current_name(button_import);
    gtk_image_set_from_file(GTK_IMAGE(image),filename);
    g_free(filename);
}
*/


void on_button_import_clicked(GtkButton *button) {
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileFilter *filter;

    // Use the main window as the parent for the dialog
    GtkWidget *parent_window = gtk_widget_get_toplevel(GTK_WIDGET(button));

    // Create a file chooser dialog
    dialog = gtk_file_chooser_dialog_new("Choose an image", GTK_WINDOW(parent_window),
                                         GTK_FILE_CHOOSER_ACTION_OPEN, 
                                         "_Cancel", GTK_RESPONSE_CANCEL, 
                                         "_Open", GTK_RESPONSE_ACCEPT, NULL);
    
    // Check if dialog is created
    if (dialog == NULL) 
    {
        g_print("Failed to create dialog\n");
        return;
    }

    chooser = GTK_FILE_CHOOSER(dialog);

    // Add file filters
    filter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter, "*.jpg");
    gtk_file_filter_add_pattern(filter, "*.jpeg");
    gtk_file_filter_add_pattern(filter, "*.png");
    gtk_file_filter_add_pattern(filter, "*.bmp");
    gtk_file_chooser_add_filter(chooser, filter);

    // Show the dialog and wait for a response
    int response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT) {
        // Free the previous file path, if any
        if (image_file_path) 
        {
            g_free(image_file_path);
        }

        image_file_path = gtk_file_chooser_get_filename(chooser);
        g_print("Selected file: %s\n", image_file_path);  // Debug output
        gtk_button_set_label(button, image_file_path);
        load_image(image_file_path);
    } 
    else 
    {
        g_print("Dialog closed without selecting a file\n");  // Debug output
    }

    // Destroy the dialog
    gtk_widget_destroy(dialog);
}
