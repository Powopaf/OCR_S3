#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>

// Functions prototypes
void get_gtk_widgets();
void on_button_import_clicked();
void on_button_reset_clicked();
void on_button_process_clicked();
void on_button_import_file_set();
void load_image(char *filename);
void on_steps_toggled(GtkToggleButton **buttons);
void on_step_0_toggled();
void on_step_1_toggled();
void on_step_2_toggled();
void on_step_3_toggled();
void on_step_4_toggled();
void on_step_5_toggled();
void on_step_6_toggled();
void on_step_7_toggled();
void on_step_8_toggled();
void on_scale_rotation_button_release_event();
void resize_images();
void resize(char *input, char *output);
gboolean on_window_resize();
void on_window_destroy();

#endif
