//GTK interface using Glade

#include "interface.h"
#include <gtk/gtk.h>

// Initialize object pointers
GtkBuilder *builder;

GtkAdjustment *adjustment_rotation;
GtkFileFilter *filter;

GtkWidget *window;
GtkWidget *box_vertical;
GtkWidget *box_horizontal;

GtkWidget *image_logo;
GtkWidget *scale_rotation;
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

GtkToggleButton *step_0;
GtkToggleButton *step_1;
GtkToggleButton *step_2;
GtkToggleButton *step_3;
GtkToggleButton *step_4;
GtkToggleButton *step_5;
GtkToggleButton *step_6;
GtkToggleButton *step_7;

GtkWidget *image;
GtkWidget *imageTMP;

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

    step_0 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_0"));
    step_1 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_1"));
    step_2 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_2"));
    step_3 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_3"));
    step_4 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_4"));
    step_5 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_5"));
    step_6 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_6"));
    step_7 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_7"));
    
    g_signal_connect(step_0, "toggled", G_CALLBACK(on_step_0_toggled), NULL);
    g_signal_connect(step_1, "toggled", G_CALLBACK(on_step_1_toggled), NULL);
    g_signal_connect(step_2, "toggled", G_CALLBACK(on_step_2_toggled), NULL);
    g_signal_connect(step_3, "toggled", G_CALLBACK(on_step_3_toggled), NULL);
    g_signal_connect(step_4, "toggled", G_CALLBACK(on_step_4_toggled), NULL);
    g_signal_connect(step_5, "toggled", G_CALLBACK(on_step_5_toggled), NULL);
    g_signal_connect(step_6, "toggled", G_CALLBACK(on_step_6_toggled), NULL);
    g_signal_connect(step_7, "toggled", G_CALLBACK(on_step_7_toggled), NULL);
    
    imageTMP = NULL;
    
    gtk_widget_show(window);
    gtk_main();
    g_object_unref(builder);
    return EXIT_SUCCESS;
}

void on_button_import_file_set()
{
    //Shows next buttons
    on_button_import_clicked();

    //Gets filename into a char array
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(button_import);
    gchar *name = gtk_file_chooser_get_filename(chooser);
    if (name == NULL)
    {
        return;
    }
    char *filename = g_strdup(name);

    //Clear the previous image
    if (image)
    {
        gtk_widget_destroy(image); 
        image = NULL;
    }
    if (imageTMP) {
        gtk_widget_destroy(imageTMP);
        imageTMP = NULL;
    }

    //Gets GTK window size to adjust the image height
    int window_width, window_height;
    gtk_window_get_size(GTK_WINDOW(window), &window_width, &window_height);
    int height = window_height;

    //Resizing the image with ImageMagick
    char cmd[2048];
    sprintf(cmd, "magick \"%s\" -resize x%d tmp.jpg", filename, height);
    system(cmd);

    //Maintain the right ratio
    sprintf(cmd, "identify -format %%wx%%h \"tmp.jpg\"\n");
    FILE *f1 = popen(cmd, "r");
    if (f1 == NULL)
    {
        g_print("Error reading image dimensions\n");
        g_free(filename);
        return;
    }
    char dimensions[512];
    fgets(dimensions, sizeof(dimensions), f1);
    pclose(f1);
    int resized_width = 1;
    int resized_height = 1;
    sscanf(dimensions, "%dx%d", &resized_width, &resized_height);

    // Load the resized image
    imageTMP = gtk_image_new_from_file("tmp.jpg");
    gtk_widget_set_halign(imageTMP, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(imageTMP, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(box_vertical), imageTMP, TRUE, TRUE, 0);
    gtk_widget_show(imageTMP);

    system("rm tmp.jpg");
    g_free(filename);
}

void on_button_import_clicked()
{
    gtk_widget_show(sep_2);
    gtk_widget_show(label_rotation);
    gtk_widget_show(scale_rotation);
    gtk_widget_show(sep_3);
    gtk_widget_show(label_process);
    gtk_widget_show(button_process);

    gtk_widget_hide(sep_4);
    gtk_widget_hide(label_steps);
    gtk_widget_hide(GTK_WIDGET(step_0));
    gtk_widget_hide(GTK_WIDGET(step_1));
    gtk_widget_hide(GTK_WIDGET(step_2));
    gtk_widget_hide(GTK_WIDGET(step_3));
    gtk_widget_hide(GTK_WIDGET(step_4));
    gtk_widget_hide(GTK_WIDGET(step_5));
    gtk_widget_hide(GTK_WIDGET(step_6));
    gtk_widget_hide(GTK_WIDGET(step_7));

}

void on_button_process_clicked()
{
    gtk_widget_show(sep_4);
    gtk_widget_show(label_steps);
    gtk_widget_show(GTK_WIDGET(step_0));
    gtk_widget_show(GTK_WIDGET(step_1));
    gtk_widget_show(GTK_WIDGET(step_2));
    gtk_widget_show(GTK_WIDGET(step_3));
    gtk_widget_show(GTK_WIDGET(step_4));
    gtk_widget_show(GTK_WIDGET(step_5));
    gtk_widget_show(GTK_WIDGET(step_6));
    gtk_widget_show(GTK_WIDGET(step_7));
}

void toggle_buttons_clicked(GtkToggleButton *active_button) {
    GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_3, step_4, step_5, step_6, step_7};

    // Check if the clicked button is already active
    if (gtk_toggle_button_get_active(active_button)) {
        return; // Exit if the active button is already checked
    }

    // Deactivate all buttons except the active one
    for (size_t i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        if (buttons[i] != active_button) {
            gtk_toggle_button_set_active(buttons[i], FALSE);
        }
    }
    // Activate the clicked button
    gtk_toggle_button_set_active(active_button, TRUE);
}


void on_step_0_toggled() {
    toggle_buttons_clicked(step_0);
}

void on_step_1_toggled() {
    toggle_buttons_clicked(step_1);
}

void on_step_2_toggled() {
    toggle_buttons_clicked(step_2);
}

void on_step_3_toggled() {
    toggle_buttons_clicked(step_3);
}

void on_step_4_toggled() {
    toggle_buttons_clicked(step_4);
}

void on_step_5_toggled() {
    toggle_buttons_clicked(step_5);
}

void on_step_6_toggled() {
    toggle_buttons_clicked(step_6);
}

void on_step_7_toggled() {
    toggle_buttons_clicked(step_7);
}
