// GTK interface using Glade and gtk3

// Includes
#include "interface.h"
#include "../../main.h"
#include "../../src/Pretreatment/rotation/rotate.h"
#include <gtk/gtk.h>

// Global variables
size_t CurrentState = 0;
int height = 1080;

// Initialize object pointers
GtkBuilder *builder;
GtkWidget *window;
GtkAdjustment *adjustment_rotation;
GtkFileFilter *filter;
GtkWidget *box_vertical;
GtkWidget *box_horizontal;
GtkWidget *box_rotation;
GtkWidget *image_logo;
GtkWidget *scale_rotation;
GtkWidget *button_import;
GtkWidget * button_reset;
GtkWidget *button_process;
GtkWidget *button_export;
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
GtkWidget *sep_6;
GtkToggleButton *step_0;
GtkToggleButton *step_1;
GtkToggleButton *step_2;
GtkToggleButton *step_3;
GtkToggleButton *step_4;
GtkToggleButton *step_5;
GtkToggleButton *step_6;
GtkToggleButton *step_7;
GtkToggleButton *step_8;
GtkWidget *image;
GtkWidget *imageTMP;

// Build objects
void get_gtk_widgets()
{
    button_import = GTK_WIDGET(gtk_builder_get_object(builder,"button_import"));
    button_reset = GTK_WIDGET(gtk_builder_get_object(builder,"button_reset"));
    label_import = GTK_WIDGET(gtk_builder_get_object(builder, "label_import"));
    label_title = GTK_WIDGET(gtk_builder_get_object(builder, "label_title"));
    image = GTK_WIDGET(gtk_builder_get_object(builder,"image"));
    box_vertical = GTK_WIDGET(gtk_builder_get_object(builder, "box_vertical"));
    box_horizontal = GTK_WIDGET(gtk_builder_get_object(builder,
                                                       "box_horizontal"));
    box_rotation = GTK_WIDGET(gtk_builder_get_object(builder,"box_rotation"));
    image_logo = GTK_WIDGET(gtk_builder_get_object(builder, "image_logo"));
    scale_rotation = GTK_WIDGET(gtk_builder_get_object(builder,
                                                       "scale_rotation"));
    adjustment_rotation = GTK_ADJUSTMENT(gtk_builder_get_object(builder,
                                                       "adjustment_rotation"));
    filter = GTK_FILE_FILTER(gtk_builder_get_object(builder, "filter"));
    button_process = GTK_WIDGET(gtk_builder_get_object(builder,
                                                       "button_process"));
    button_export = GTK_WIDGET(gtk_builder_get_object(builder,
                                                      "button_export"));
    label_rotation = GTK_WIDGET(gtk_builder_get_object(builder,
                                                       "label_rotation"));
    label_process = GTK_WIDGET(gtk_builder_get_object(builder,
                                                      "label_process"));
    label_steps = GTK_WIDGET(gtk_builder_get_object(builder, "label_steps"));
    sep_1 = GTK_WIDGET(gtk_builder_get_object(builder, "sep_1"));
    sep_2 = GTK_WIDGET(gtk_builder_get_object(builder, "sep_2"));
    sep_3 = GTK_WIDGET(gtk_builder_get_object(builder, "sep_3"));
    sep_4 = GTK_WIDGET(gtk_builder_get_object(builder, "sep_4"));
    sep_5 = GTK_WIDGET(gtk_builder_get_object(builder, "sep_5"));
    sep_6 = GTK_WIDGET(gtk_builder_get_object(builder, "sep_6"));
    step_0 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_0"));
    step_1 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_1"));
    step_2 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_2"));
    step_3 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_3"));
    step_4 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_4"));
    step_5 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_5"));
    step_6 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_6"));
    step_7 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_7"));
    step_8 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "step_8"));
}

// Main loop
int main(int argc, char *argv[]) 
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Read the XML glade file
    builder = gtk_builder_new_from_file("src/Gtk/interface.glade");

    // Build the GTK window
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    gtk_window_set_title(GTK_WINDOW(window), "CLAPS Word Search OCR");

    // Modify height on window resize
    g_signal_connect(window, "configure-event",
                     G_CALLBACK(on_window_resize), NULL);

    // Destroy program on application exit
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);
    
    // Build the signal table
    gtk_builder_connect_signals(builder, NULL);
    
    // Build GTK objects
    get_gtk_widgets();

    gtk_widget_show(window);
    gtk_main();
    g_object_unref(builder);
    return EXIT_SUCCESS;
}

// Activate on window resize event
gboolean on_window_resize()
{
    int window_width, window_height;
    gtk_window_get_size(GTK_WINDOW(window), &window_width, &window_height);
    height = window_height;   
    return FALSE;
}

// Activate on window destroy event
void on_window_destroy()
{
    // Remove temporary files and quit
    system("rm output/*.bmp");
    //METTRE SHELL QUI SUPPRIME TOUTES LES LETTERS
    gtk_main_quit();
}

// Load the image on the right box of the window
void load_image(char *filename)
{
    // Clear the previous image
    if (image)
    {
        gtk_widget_destroy(image);
        image = NULL;
    }

    // Load the image
    image = gtk_image_new_from_file(filename);
    gtk_widget_set_halign(image, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(image, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(box_vertical), image, TRUE, TRUE, 0);
    gtk_widget_show(image);
}

void resize_images()
{
    // Resize all images 
    resize("output/imgGreyScale.bmp","output/RimgGreyScale.bmp");
    resize("output/imgNoiseReduction.bmp","output/RimgNoiseReduction.bmp");
    resize("output/imgBinarisation.bmp","output/RimgBinarisation.bmp");
    resize("output/imgFindShape.bmp","output/RimgFindShape.bmp");
    resize("output/imgShapeFilter.bmp","output/RimgShapeFilter.bmp");
    resize("output/imgFindCluster.bmp","output/RimgFindCluster.bmp");
    resize("output/imgClusterFilter.bmp","output/RimgClusterFilter.bmp");
    resize("output/imgFinal.bmp","output/RimgFinal.bmp");
}

// Convert and resize the image
void resize(char *input, char *output)
{
    // Convert and resize with ImageMagick (only for the interface)
    char cmd[2048];
    sprintf(cmd,"magick \"%s\" -resize x%d -sharpen 0x1.0 -quality 100 \"%s\"",
        input, height, output);
    system(cmd);
}

// On button import click
void on_button_import_file_set()
{
    // Show next buttons
    on_button_import_clicked();
    
    // Reset rotation
    gtk_adjustment_set_value(adjustment_rotation,0);
    
    // Get filename into a char*
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(button_import);
    gchar *name = gtk_file_chooser_get_filename(chooser);
    if (name == NULL) return;
    
    char cmd[2048];
    sprintf(cmd, "magick \"%s\" output/img.bmp", name);
    system(cmd);
    
    sprintf(cmd, "magick \"%s\" output/original.bmp", name);
    system(cmd);
    
    g_free(name);
    
    resize("output/img.bmp","output/Rimg.bmp");
    CurrentState = 0;
    load_image("output/Rimg.bmp");
}

// On import button click
void on_button_import_clicked()
{
    // Show rotation and process button
    gtk_widget_show(sep_2);
    gtk_widget_show(box_rotation);
    gtk_widget_show(label_rotation);
    gtk_widget_show(button_reset);
    gtk_widget_show(scale_rotation);
    gtk_widget_show(sep_3);
    gtk_widget_show(label_process);
    gtk_widget_show(button_process);

    // Hide process steps and export button
    gtk_widget_hide(sep_4);
    gtk_widget_hide(sep_6);
    gtk_widget_hide(button_export);
    gtk_widget_hide(label_steps);
    gtk_widget_hide(GTK_WIDGET(step_0));
    gtk_widget_hide(GTK_WIDGET(step_1));
    gtk_widget_hide(GTK_WIDGET(step_2));
    gtk_widget_hide(GTK_WIDGET(step_3));
    gtk_widget_hide(GTK_WIDGET(step_4));
    gtk_widget_hide(GTK_WIDGET(step_5));
    gtk_widget_hide(GTK_WIDGET(step_6));
    gtk_widget_hide(GTK_WIDGET(step_7));
    gtk_widget_hide(GTK_WIDGET(step_8));
}

// On process button click
void on_button_process_clicked()
{
    // Process the image
    Process("output/img.bmp");
    resize_images();
    load_image("output/RimgFinal.bmp");

    // Select the solution image by default
    GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_3, step_4,
                                  step_5, step_6, step_7, step_8};
    on_steps_toggled(buttons);
    if (!gtk_toggle_button_get_active(step_8))
    {
        gtk_toggle_button_set_active(step_8, TRUE);
    }
    // Show process steps and export button
    gtk_widget_show(sep_4);
    gtk_widget_show(sep_6);
    gtk_widget_show(button_export);
    gtk_widget_show(label_steps);
    gtk_widget_show(GTK_WIDGET(step_0));
    gtk_widget_show(GTK_WIDGET(step_1));
    gtk_widget_show(GTK_WIDGET(step_2));
    gtk_widget_show(GTK_WIDGET(step_3));
    gtk_widget_show(GTK_WIDGET(step_4));
    gtk_widget_show(GTK_WIDGET(step_5));
    gtk_widget_show(GTK_WIDGET(step_6));
    gtk_widget_show(GTK_WIDGET(step_7));
    gtk_widget_show(GTK_WIDGET(step_8));
    
    // Hide rotation and process button
    gtk_widget_hide(sep_2);
    gtk_widget_hide(box_rotation);
    gtk_widget_hide(label_rotation);
    gtk_widget_hide(button_reset);
    gtk_widget_hide(scale_rotation);
    gtk_widget_hide(sep_3);
    gtk_widget_hide(label_process);
    gtk_widget_hide(button_process);
}

void on_step_0_toggled()
{
    if (gtk_toggle_button_get_active(step_0))
    {
        GtkToggleButton *buttons[] = {step_1, step_2, step_3, step_4,
                                      step_5, step_6, step_7, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 0;
    load_image("output/Rimg.bmp");
}

void on_step_1_toggled()
{
    if (gtk_toggle_button_get_active(step_1))
    {
        GtkToggleButton *buttons[] = {step_0, step_2, step_3, step_4,
                                      step_5, step_6, step_7, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 1;
    load_image("output/RimgGreyScale.bmp");
}

void on_step_2_toggled()
{
    if (gtk_toggle_button_get_active(step_2))
    {
        GtkToggleButton *buttons[] = {step_0, step_1, step_3, step_4,
                                      step_5, step_6, step_7, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 2;
    load_image("output/RimgNoiseReduction.bmp");
}

void on_step_3_toggled()
{
    if (gtk_toggle_button_get_active(step_3))
    {
        GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_4,
                                      step_5, step_6, step_7, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 3;
    load_image("output/RimgBinarisation.bmp");
}

void on_step_4_toggled()
{
    if (gtk_toggle_button_get_active(step_4))
    {
        GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_3,
                                      step_5, step_6, step_7, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 4;
    load_image("output/RimgFindShape.bmp");
}

void on_step_5_toggled()
{
    if (gtk_toggle_button_get_active(step_5))
    {
        GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_3,
                                      step_4, step_6, step_7, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 5;
    load_image("output/RimgShapeFilter.bmp");
}

void on_step_6_toggled()
{
    if (gtk_toggle_button_get_active(step_6))
    {
        GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_3,
                                      step_4, step_5, step_7, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 6;
    load_image("output/RimgFindCluster.bmp");
}

void on_step_7_toggled()
{
    if (gtk_toggle_button_get_active(step_7))
    {
        GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_3,
                                      step_4, step_5, step_6, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 7;
    load_image("output/RimgClusterFilter.bmp");
}

void on_step_8_toggled()
{
    if (gtk_toggle_button_get_active(step_8))
    {
        GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_3,
                                      step_4, step_5, step_6, step_7};
        on_steps_toggled(buttons);
    }
    CurrentState = 8;
    load_image("output/RimgFinal.bmp");
}

void on_steps_toggled(GtkToggleButton *buttons[])
{
    for (size_t i = 0; i < 8; i++)
    {
        gtk_toggle_button_set_active(buttons[i], FALSE);
    }
}

// On slider click, adjust the rotation
void on_scale_rotation_button_release_event()
{
    gdouble value = gtk_adjustment_get_value(adjustment_rotation);
    rotation("output/original.bmp",value,"output/img.bmp");
    resize("output/img.bmp","output/Rimg.bmp");
    
    CurrentState = 0;
    load_image("output/Rimg.bmp");
}

// On reset button click, reset the image
void on_button_reset_clicked()
{
    gtk_adjustment_set_value(adjustment_rotation,0);
    char cmd[2048];
    sprintf(cmd, "cp output/original.bmp output/img.bmp");
    system(cmd);
    
    resize("output/img.bmp","output/Rimg.bmp");
    
    CurrentState = 0;
    load_image("output/Rimg.bmp");
}

// On button export click
void on_button_export_clicked()
{
    // Create a file chooser dialog to save the current image
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;
    dialog = gtk_file_chooser_dialog_new("Save Image",
                                         GTK_WINDOW(window),
                                         action,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "Save",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    // Enable overwrite confirmation
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog),
                                                   TRUE);

    // Default filename
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog),"solution.png");

    // Wait for user response
    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        chooser = GTK_FILE_CHOOSER(dialog);
        gchar *export_filename = gtk_file_chooser_get_filename(chooser);
        const char* image_paths[] =
        {
            "output/img.bmp",               // State 0: Original image
            "output/imgGreyScale.bmp",      // State 1: Greyscale image
            "output/imgNoiseReduction.bmp", // State 2: Noise Reduction image
            "output/imgBinarisation.bmp",   // State 3: Binarisation image
            "output/imgFindShape.bmp",      // State 4: Find Shape image
            "output/imgShapeFilter.bmp",    // State 5: Shape Filter image
            "output/imgFindCluster.bmp",    // State 6: Find Cluster image
            "output/imgClusterFilter.bmp",  // State 7: Cluster Filter image
            "output/imgFinal.bmp"           // State 8: Final image
        };

        char cmd[2048];
        sprintf(cmd, "magick \"%s\" \"%s\"", image_paths[CurrentState],
                export_filename);
        system(cmd);

        g_free(export_filename);
    }
    gtk_widget_destroy(dialog);
}

