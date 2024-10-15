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

GtkWidget *step_0;
GtkWidget *step_1;
GtkWidget *step_2;
GtkWidget *step_3;
GtkWidget *step_4;
GtkWidget *step_5;
GtkWidget *step_6;
GtkWidget *step_7;

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

    step_0 = GTK_WIDGET(gtk_builder_get_object(builder, "step_0"));
    step_1 = GTK_WIDGET(gtk_builder_get_object(builder, "step_1"));
    step_2 = GTK_WIDGET(gtk_builder_get_object(builder, "step_2"));
    step_3 = GTK_WIDGET(gtk_builder_get_object(builder, "step_3"));
    step_4 = GTK_WIDGET(gtk_builder_get_object(builder, "step_4"));
    step_5 = GTK_WIDGET(gtk_builder_get_object(builder, "step_5"));
    step_6 = GTK_WIDGET(gtk_builder_get_object(builder, "step_6"));
    step_7 = GTK_WIDGET(gtk_builder_get_object(builder, "step_7"));
    
    imageTMP = NULL;
    
    gtk_widget_show(window);
    gtk_main();
    return EXIT_SUCCESS;
}

void on_button_import_file_set()
{
    //NOT WORKING
    gtk_label_set_text(GTK_LABEL(label_import),(const gchar*)"Import image from device files");
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(button_import);
    gchar *name = gtk_file_chooser_get_filename(chooser);
    //gtk_image_set_from_file(GTK_IMAGE(image),filename);
    //g_free(filename);
    int len = strlen(name);
    char filename[len + 1];
    strcpy(filename, name);

    //char filename[] = filename;
    char cmd[2048];
    FILE *f1;
    size_t j;
    int h;
    int v;
    int hor = 150;
    int ver = 1;
    
    on_button_import_clicked();

    if (imageTMP)
    {
    	gtk_container_remove(GTK_CONTAINER (box_vertical), imageTMP); // remove old slide
    }
    gtk_widget_hide(image);

    //Get dimensions of image with identify (ImageMagick)

    sprintf(cmd, "identify -format %%wx%%h \"%s\"\n", filename);
    f1 = popen(cmd, "r");
    strcpy(cmd, "");
    fgets(cmd, 512, f1);
    fclose(f1);

	h = v = 1;

	if (strlen(cmd))
	{
		for (j = 0; j < strlen(cmd) - 1; j++)
        {
            if (cmd[j] == 'x')
            {
                break;
            }
        }

        if (cmd[j] == 'x')
        {
			cmd[j] = 0;
			sscanf(cmd, "%d", &h);
			sscanf(&cmd[j+1], "%d", &v);
		}
	}

    //Resize the image with convert (ImageMagick)

    int width = 900; 
    int height = 700;

    sprintf(cmd, "magick \"%s\" -resize %dx%d tmp.jpg", filename, width, height);
    system(cmd);

    strcpy(filename,"tmp.jpg");

//	Get new image dimensions  - actual dimensions will be in the
//	range of the conversion. Conversion will maintain ratio.

    sprintf(cmd, "identify -format %%wx%%h \"%s\"\n", filename);
    f1 = popen(cmd, "r");
    strcpy(cmd,"");
    fgets(cmd, 512, f1);
    fclose(f1);
    h = v = 1;

    if (strlen(cmd)) 
    {
        for (j = 0; j < strlen(cmd) - 1; j++) 
            if (cmd[j] == 'x') 
                break;

        if (cmd[j] == 'x')
        {
            cmd[j] = 0;
            sscanf(cmd, "%d", &h);
            sscanf(&cmd[j+1], "%d", &v);
        }
    }

//h and v are now the actual new dimensions which you can use
//to better center your image in the GUI

	imageTMP = gtk_image_new_from_file(filename);

	gtk_container_add (GTK_CONTAINER(box_vertical), imageTMP);
	gtk_widget_show(imageTMP);

	gtk_fixed_move (GTK_FIXED(box_vertical), imageTMP, hor, ver);

	system("rm tmp.jpg");
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
    gtk_widget_hide(step_0);
    gtk_widget_hide(step_1);
    gtk_widget_hide(step_2);
    gtk_widget_hide(step_3);
    gtk_widget_hide(step_4);
    gtk_widget_hide(step_5);
    gtk_widget_hide(step_6);
    gtk_widget_hide(step_7);

}

void on_button_process_clicked()
{
    gtk_widget_show(sep_4);
    gtk_widget_show(label_steps);
    gtk_widget_show(step_0);
    gtk_widget_show(step_1);
    gtk_widget_show(step_2);
    gtk_widget_show(step_3);
    gtk_widget_show(step_4);
    gtk_widget_show(step_5);
    gtk_widget_show(step_6);
    gtk_widget_show(step_7);
}

void toggle_button_clicked(GtkToggleButton *toggled_button)
{
    //Cast GtkWidget* to GtkToggleButton*
    GtkToggleButton *buttons[] =
    {
        GTK_TOGGLE_BUTTON(step_0),
        GTK_TOGGLE_BUTTON(step_1),
        GTK_TOGGLE_BUTTON(step_2),
        GTK_TOGGLE_BUTTON(step_3),
        GTK_TOGGLE_BUTTON(step_4),
        GTK_TOGGLE_BUTTON(step_5),
        GTK_TOGGLE_BUTTON(step_6),
        GTK_TOGGLE_BUTTON(step_7)
    };

    for (int i = 0; i < 8; i++)
    {
        if (buttons[i] != toggled_button)
        {
            gtk_toggle_button_set_active(buttons[i], FALSE);
        }
    }
}

void on_step_0_toggled()
{
    toggle_button_clicked(GTK_TOGGLE_BUTTON(step_0));
}

void on_step_1_toggled()
{
    toggle_button_clicked(GTK_TOGGLE_BUTTON(step_1));
}

void on_step_2_toggled()
{
    toggle_button_clicked(GTK_TOGGLE_BUTTON(step_2));
}

void on_step_3_toggled()
{
    toggle_button_clicked(GTK_TOGGLE_BUTTON(step_3));
}

void on_step_4_toggled()
{
    toggle_button_clicked(GTK_TOGGLE_BUTTON(step_4));
}

void on_step_5_toggled()
{
    toggle_button_clicked(GTK_TOGGLE_BUTTON(step_5));
}

void on_step_6_toggled()
{
    toggle_button_clicked(GTK_TOGGLE_BUTTON(step_6));
}

void on_step_7_toggled()
{
    toggle_button_clicked(GTK_TOGGLE_BUTTON(step_7));
}
