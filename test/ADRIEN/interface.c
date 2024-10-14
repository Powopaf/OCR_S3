//GTK interface

//#include <stdlib.h>
#include <gtk/gtk.h>

// Initialize object pointers
GtkBuilder *builder;

GtkAdjustment *adjustment_rotation;
GtkFileFilter *filter;

GtkWidget *window;
GtkWidget *box_vertical;
GtkWidget *box_horizontal;

GtkWidget *image_logo;
GtkWidget *image;
GtkWidget *scale_rotation;
GtkWidget *progress_bar;
GtkWidget *button_import;
GtkWidget *button_process;

GtkWidget *label_title;
GtkWidget *label_import;
GtkWidget *label_rotation;
GtkWidget *label_process;
GtkWidget *label_steps;

GtkWidget *sep_1;
GtkWidget *sep_2;
GtkWidget *sep_3;
GtkWidget *sep_4;
GtkWidget *sep_5;

GtkWidget *step_0;
GtkWidget *step_1;
GtkWidget *step_2;
GtkWidget *step_3;
GtkWidget *step_4;
GtkWidget *step_5;
GtkWidget *step_6;
GtkWidget *step_7;


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
    button_import = GTK_WIDGET(gtk_builder_get_object(builder,"button_import"));
    label_import = GTK_WIDGET(gtk_builder_get_object(builder, "label_import"));
    label_title = GTK_WIDGET(gtk_builder_get_object(builder, "label_title"));
    image = GTK_WIDGET(gtk_builder_get_object(builder,"image"));
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    box_vertical = GTK_WIDGET(gtk_builder_get_object(builder, "box_vertical"));
    box_horizontal = GTK_WIDGET(gtk_builder_get_object(builder, "box_horizontal"));
    image_logo = GTK_WIDGET(gtk_builder_get_object(builder, "image_logo"));
    scale_rotation = GTK_WIDGET(gtk_builder_get_object(builder, "scale_rotation"));
    adjustment_rotation = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_rotation"));
    filter = GTK_FILE_FILTER(gtk_builder_get_object(builder, "filter"));
    progress_bar = GTK_WIDGET(gtk_builder_get_object(builder, "progress_bar"));
    button_process = GTK_WIDGET(gtk_builder_get_object(builder, "button_process"));

    label_import = GTK_WIDGET(gtk_builder_get_object(builder, "label_import"));
    label_rotation = GTK_WIDGET(gtk_builder_get_object(builder, "label_rotation"));
    label_process = GTK_WIDGET(gtk_builder_get_object(builder, "label_process"));
    label_steps = GTK_WIDGET(gtk_builder_get_object(builder, "label_steps"));

    sep_1 = GTK_WIDGET(gtk_builder_get_object(builder, "sep_1"));
    sep_2 = GTK_WIDGET(gtk_builder_get_object(builder, "sep_2"));
    sep_3 = GTK_WIDGET(gtk_builder_get_object(builder, "sep_3"));
    sep_4 = GTK_WIDGET(gtk_builder_get_object(builder, "sep_4"));
    sep_5 = GTK_WIDGET(gtk_builder_get_object(builder, "sep_5"));

    step_0 = GTK_WIDGET(gtk_builder_get_object(builder, "step_0"));
    step_1 = GTK_WIDGET(gtk_builder_get_object(builder, "step_1"));
    step_2 = GTK_WIDGET(gtk_builder_get_object(builder, "step_2"));
    step_3 = GTK_WIDGET(gtk_builder_get_object(builder, "step_3"));
    step_4 = GTK_WIDGET(gtk_builder_get_object(builder, "step_4"));
    step_5 = GTK_WIDGET(gtk_builder_get_object(builder, "step_5"));
    step_6 = GTK_WIDGET(gtk_builder_get_object(builder, "step_6"));
    step_7 = GTK_WIDGET(gtk_builder_get_object(builder, "step_7"));
    
    
    gtk_widget_show(window);
    gtk_main();
    return EXIT_SUCCESS;
}

void on_button_import_clicked()
{
    gtk_label_set_text(GTK_LABEL(label_import),(const gchar*)
    "Import image from device files");
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(button_import);
    gchar *filename = gtk_file_chooser_get_filename(chooser);
    gtk_image_set_from_file(GTK_IMAGE(image),filename);
    g_free(filename);
}
