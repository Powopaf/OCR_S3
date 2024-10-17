// GTK interface using Glade and gtk3
#include "interface.h"
#include "../../main.h"
#include "../../src/Pretreatment/rotation/rotate.h"
#include <gtk/gtk.h>

// Global variables
size_t CurrentState = 0;
int height = 1080;

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

// Builds objects
void get_gtk_widgets()
{
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
    button_export = GTK_WIDGET(gtk_builder_get_object(builder, "button_export"));
    label_rotation = GTK_WIDGET(gtk_builder_get_object(builder, "label_rotation"));
    label_process = GTK_WIDGET(gtk_builder_get_object(builder, "label_process"));
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

int main(int argc, char *argv[]) 
{
    // Initialize GTK
    gtk_disable_setlocale();
    gtk_init(&argc, &argv);

    // Reads the XML glade file
    builder = gtk_builder_new_from_file("src/Gtk/interface.glade");

    // Builds the GTK window
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    gtk_window_set_title(GTK_WINDOW(window), "CLAPS Word Search OCR");

    // Modify height on window resize
    g_signal_connect(window, "configure-event", G_CALLBACK(on_window_resize), NULL);

    // Destroys program on application exit
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

    // Builds a table to see where does the signals come from
    gtk_builder_connect_signals(builder, NULL);
    
    // Building GTK objects
    get_gtk_widgets();

    imageTMP = NULL;

    gtk_widget_show(window);
    gtk_main();
    g_object_unref(builder);
    return EXIT_SUCCESS;
}

// Activates on window resize event
gboolean on_window_resize()
{
    int window_width, window_height;
    gtk_window_get_size(GTK_WINDOW(window), &window_width, &window_height);
    height = window_height;   
    return FALSE;
}

// Activates on window destroy event
void on_window_destroy()
{
    system("rm output/*.bmp");
    system("rm output/letter/*.bmp");
    gtk_main_quit();
}

void load_image(char *filename)
{
    // Clear the previous image
    if (image)
    {
        gtk_widget_destroy(image);
        image = NULL;
    }
    if (imageTMP)
    {
        gtk_widget_destroy(imageTMP);
        imageTMP = NULL;
    }

    // Load the image
    imageTMP = gtk_image_new_from_file(filename);
    gtk_widget_set_halign(imageTMP, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(imageTMP, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(box_vertical), imageTMP, TRUE, TRUE, 0);
    gtk_widget_show(imageTMP);

    // Copy the loaded image to output directory
    //char cmd[2048];
    //sprintf(cmd, "cp \"%s\" output/tmp.bmp", filename);
    //system(cmd);
}

void resize_images()
{
    resize("output/imgGreyScale.bmp","output/RimgGreyScale.bmp");
    resize("output/imgNoiseReduction.bmp","output/RimgNoiseReduction.bmp");
    resize("output/imgBinarisation.bmp","output/RimgBinarisation.bmp");
    resize("output/imgFindShape.bmp","output/RimgFindShape.bmp");
    resize("output/imgShapeFilter.bmp","output/RimgShapeFilter.bmp");
    resize("output/imgFindCluster.bmp","output/RimgFindCluster.bmp");
    resize("output/imgClusterFilter.bmp","output/RimgClusterFilter.bmp");
    resize("output/imgFinal.bmp","output/RimgFinal.bmp");
}


void resize(char *input, char *output)
{
    // Convert and resize with ImageMagick (only for the interface)
    char cmd[2048];
    sprintf(cmd, "magick \"%s\" -resize x%d -sharpen 0x1.0 -quality 100 \"%s\"",
        input, height, output);
    system(cmd);
}

void on_button_import_file_set()
{
    // Shows next buttons
    on_button_import_clicked();

    // Gets filename into a char*
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(button_import);
    gchar *name = gtk_file_chooser_get_filename(chooser);
    if (name == NULL)
    {
        return;
    }
    
    char cmd[2048];
    sprintf(cmd, "cp \"%s\" output/img.bmp", name);
    system(cmd);
    
    resize("output/img.bmp","output/Rimg.bmp");
    
    char cmd2[2048];
    sprintf(cmd2, "cp \"%s\" output/original.bmp", name);
    system(cmd2);
    
    CurrentState = 0;
    load_image("output/Rimg.bmp");
    
    g_free(name);
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

void on_button_process_clicked()
{
    // Process the image
    Process("output/img.bmp");
    load_image("output/RimgFinal.bmp");
    resize_images();

    GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_3, step_4, step_5, step_6, step_7, step_8};
    on_steps_toggled(buttons);
    if (!gtk_toggle_button_get_active(step_8))
    {
        gtk_toggle_button_set_active(step_8, TRUE);
    }
    // Shows process steps and export button
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
    gtk_widget_hide(label_rotation);
    gtk_widget_hide(scale_rotation);
    gtk_widget_hide(sep_3);
    gtk_widget_hide(label_process);
    gtk_widget_hide(button_process);
}

void on_step_0_toggled()
{
    if (gtk_toggle_button_get_active(step_0))
    {
        GtkToggleButton *buttons[] = {step_1, step_2, step_3, step_4, step_5, step_6, step_7, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 0;
    load_image("output/Rimg.bmp");
}

void on_step_1_toggled()
{
    if (gtk_toggle_button_get_active(step_1))
    {
        GtkToggleButton *buttons[] = {step_0, step_2, step_3, step_4, step_5, step_6, step_7, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 1;
    load_image("output/RimgGreyScale.bmp");
}

void on_step_2_toggled()
{
    if (gtk_toggle_button_get_active(step_2))
    {
        GtkToggleButton *buttons[] = {step_0, step_1, step_3, step_4, step_5, step_6, step_7, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 2;
    load_image("output/RimgNoiseReduction.bmp");
}

void on_step_3_toggled()
{
    if (gtk_toggle_button_get_active(step_3))
    {
        GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_4, step_5, step_6, step_7, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 3;
    load_image("output/RimgBinarisation.bmp");
}

void on_step_4_toggled()
{
    if (gtk_toggle_button_get_active(step_4))
    {
        GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_3, step_5, step_6, step_7, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 4;
    load_image("output/RimgFindShape.bmp");
}

void on_step_5_toggled()
{
    if (gtk_toggle_button_get_active(step_5))
    {
        GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_3, step_4, step_6, step_7, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 5;
    load_image("output/RimgShapeFilter.bmp");
}

void on_step_6_toggled()
{
    if (gtk_toggle_button_get_active(step_6))
    {
        GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_3, step_4, step_5, step_7, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 6;
    load_image("output/RimgFindCluster.bmp");
}

void on_step_7_toggled()
{
    if (gtk_toggle_button_get_active(step_7))
    {
        GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_3, step_4, step_5, step_6, step_8};
        on_steps_toggled(buttons);
    }
    CurrentState = 7;
    load_image("output/RimgClusterFilter.bmp");
}

void on_step_8_toggled()
{
    if (gtk_toggle_button_get_active(step_8))
    {
        GtkToggleButton *buttons[] = {step_0, step_1, step_2, step_3, step_4, step_5, step_6, step_7};
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


void on_adjustment_rotation_value_changed()
{
    gdouble value = gtk_adjustment_get_value(adjustment_rotation);
    rotation("output/original.bmp",value,"output/img.bmp");
    
    resize("output/img.bmp","output/Rimg.bmp");
    
    CurrentState = 0;
    load_image("output/img.bmp");
}

void on_button_export_clicked()
{
    //EXPORT FUNCTION
}
