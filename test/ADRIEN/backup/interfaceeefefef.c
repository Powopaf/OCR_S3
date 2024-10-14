#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

GtkWidget *image_area;
char *image_file_path = NULL;
SDL_Surface *image_surface = NULL;
double rotation_angle = 0;

// Function to load and display the image in the drawing area
void load_image(const char *filename) {
    // Free previous image
    if (image_surface != NULL) {
        SDL_FreeSurface(image_surface);
        image_surface = NULL;
    }

    // Load the image using SDL
    image_surface = IMG_Load(filename);
    if (!image_surface) {
        g_print("Error loading image: %s\n", IMG_GetError());
        return;
    }

    // Log the dimensions of the loaded image
    g_print("Image loaded: %s (Width: %d, Height: %d)\n", filename, image_surface->w, image_surface->h);

    // Queue a redraw of the drawing area
    gtk_widget_queue_draw(image_area);
}

void on_draw_image(GtkWidget *widget, cairo_t *cr, gpointer data) {
    if (image_surface) {
        // Check if the image format is RGB, since Cairo expects a specific format
        SDL_LockSurface(image_surface);

        // Ensure the SDL surface uses a 32-bit format (ARGB8888 or RGB888)
        if (image_surface->format->BitsPerPixel != 32) {
            g_print("Unsupported image format. The image must be 32-bit.\n");
            SDL_UnlockSurface(image_surface);
            return;
        }

        cairo_surface_t *cairo_image_surface = cairo_image_surface_create_for_data(
            (unsigned char *)image_surface->pixels,
            CAIRO_FORMAT_RGB24,  // Match the image format
            image_surface->w,
            image_surface->h,
            image_surface->pitch
        );

        // Apply translation and rotation
        cairo_translate(cr, gtk_widget_get_allocated_width(widget) / 2, gtk_widget_get_allocated_height(widget) / 2);
        cairo_rotate(cr, rotation_angle * (M_PI / 180.0));
        cairo_translate(cr, -image_surface->w / 2, -image_surface->h / 2);

        // Draw the image
        cairo_set_source_surface(cr, cairo_image_surface, 0, 0);
        cairo_paint(cr);
        cairo_surface_destroy(cairo_image_surface);

        SDL_UnlockSurface(image_surface);
    } else {
        g_print("No image to draw.\n");
    }
}

void on_load_image_clicked(GtkButton *button, gpointer data) {
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
    if (dialog == NULL) {
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
        if (image_file_path) {
            g_free(image_file_path);
        }

        image_file_path = gtk_file_chooser_get_filename(chooser);
        g_print("Selected file: %s\n", image_file_path);  // Debug output
        gtk_button_set_label(button, image_file_path);
        load_image(image_file_path);
    } else {
        g_print("Dialog closed without selecting a file\n");  // Debug output
    }

    // Destroy the dialog
    gtk_widget_destroy(dialog);
}


void on_rotation_slider_changed(GtkRange *range, gpointer data) {
    rotation_angle = gtk_range_get_value(range);
    gtk_widget_queue_draw(image_area);  // Redraw the image
}

void on_process_button_clicked(GtkButton *button, gpointer data) {
    // Save the processed image in the current directory
    if (image_surface) {
        if (SDL_SaveBMP(image_surface, "processed_image.bmp") == 0) {
            g_print("Image processed and saved as processed_image.bmp\n");
        } else {
            g_print("Error saving image: %s\n", SDL_GetError());
        }
    } else {
        g_print("No image to process.\n");
    }
}

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window;

    gtk_init(&argc, &argv);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

    // Check if the Glade file exists
    if (!g_file_test("interface.glade", G_FILE_TEST_EXISTS)) {
        g_print("interface.glade file not found\n");
        return 1;
    }

    // Load the Glade interface file
    builder = gtk_builder_new_from_file("interface.glade");
    if (!builder) {
        g_print("Error loading interface.glade\n");
        return 1;
    }

    // Get the main window and image area from the Glade file
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    image_area = GTK_WIDGET(gtk_builder_get_object(builder, "image_area"));

    // Check if we successfully loaded the widgets
    if (!window || !image_area) {
        g_print("Error loading widgets from Glade file.\n");
        return 1;
    }

    // Connect signals from the Glade file to the functions in C
    gtk_builder_connect_signals(builder, NULL);

    // Free the builder after connecting signals
    g_object_unref(builder);

    // Show the main window
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    // Clean up SDL resources
    if (image_surface != NULL) {
        SDL_FreeSurface(image_surface);
    }
    IMG_Quit();

    return 0;
}

