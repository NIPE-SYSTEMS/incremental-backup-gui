#define UNUSED(x) (void)(x)

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <glib/gi18n.h>

GtkWidget *window;
GtkWidget *grid;
GtkWidget *button_path;
GtkWidget *button_source;
GtkWidget *header_bar;
GtkWidget *textview;
GtkTextBuffer *textbuffer;
GtkWidget *cb_algorithm;
GtkWidget *cb_skip_hidden;
GtkWidget *cb_full;
GtkWidget *cb_verbose;
GtkWidget *cb_yes;
GtkWidget *label1;

int main()
{
	gtk_init (NULL, NULL);
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	grid = gtk_grid_new ();
	button_path = gtk_file_chooser_button_new (_("Select a directory"), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	button_source = gtk_file_chooser_button_new (_("Select a directory"), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER (button_path), "/home/");
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER (button_source), "/");
	header_bar = gtk_header_bar_new ();
	textview = gtk_text_view_new ();
	textbuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
	cb_algorithm = gtk_combo_box_text_new ();
	cb_skip_hidden = gtk_check_button_new_with_label ("Skip hidden files. (leading '.' in file name)");
	cb_full = gtk_check_button_new_with_label ("Ignore index file and make a full backup");
	cb_verbose = gtk_check_button_new_with_label ("Verbose output");
	cb_yes = gtk_check_button_new_with_label ("Answer all questions with yes (script-friendly)"); 
	label1 = gtk_label_new("Command: ");
	
	// GTK COMBO BOX
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 0, "id1", "b64encode");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 0, "id2", "bzip2");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 0, "id3", "compress");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 0, "id4", "grzip");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 0, "id5", "lrzip");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 0, "id6", "lzip");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 0, "id7", "lzop");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 0, "id8", "uuencode");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 0, "id9", "xz");
	gtk_combo_box_set_active(GTK_COMBO_BOX(cb_algorithm), 0);

	// GTK GRID
	gtk_grid_attach (GTK_GRID (grid), button_path, 2, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), cb_algorithm, 2, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), button_source, 2, 3, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), cb_skip_hidden, 2, 5, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), cb_full, 2, 6, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), cb_verbose, 2, 7, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), cb_yes, 2, 8, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), label1, 1, 9, 1, 1);
	gtk_grid_attach_next_to (GTK_GRID (grid), textview, label1, GTK_POS_RIGHT, 1, 1);
	
	// GTK HEADER BAR
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
	gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);
	gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "Incremental Backup GUI");
	//gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header_bar), "a|a|C|C|G");

	//GTK WINDOW
	gtk_window_set_default_size((GTK_WINDOW(window)), 800, 800);

	//GTK TEXT VIEW
	gtk_text_buffer_set_text(textbuffer, "a|C|a|C|a|a|a|C|C|G|", -1);


	gtk_container_add (GTK_CONTAINER (window), grid);

	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	gtk_widget_show_all(window);
	gtk_main();
	
	return 0;
}
