#define UNUSED(x) (void)(x)

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <glib/gi18n.h>

GtkWidget *window;
//~ GtkWidget *grid;
GtkWidget *button_path;
GtkWidget *button_source;
GtkWidget *button_index;
GtkWidget *header_bar;
GtkWidget *textview;
GtkTextBuffer *textbuffer;
GtkWidget *cb_algorithm;
GtkWidget *cb_skip_hidden;
GtkWidget *cb_full;
GtkWidget *cb_verbose;
GtkWidget *cb_yes;
GtkWidget *label1;
GtkWidget *label_path;
GtkWidget *label_algorithm;
GtkWidget *label_source;
GtkWidget *label_index;
GtkWidget *spinner;

GtkWidget *scrolled_window;
GtkWidget *vertical;
GtkWidget *horizontal1;
GtkWidget *horizontal2;
GtkWidget *horizontal3;
GtkWidget *horizontal4;
GtkWidget *horizontal5;
GtkWidget *horizontal6;
GtkWidget *horizontal7;
GtkWidget *horizontal8;
GtkWidget *horizontal9;
GtkWidget *horizontal10;
GtkWidget *horizontal11;
GtkWidget *horizontal12;

int main()
{
	gtk_init (NULL, NULL);
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	//~ grid = gtk_grid_new ();
	button_path = gtk_file_chooser_button_new (_("Select a directory"), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	button_source = gtk_file_chooser_button_new (_("Select a directory"), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	button_index = gtk_file_chooser_button_new (_("Select a directory"), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER (button_path), "/home/");
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER (button_source), "/");
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER (button_source), "/home/");
	header_bar = gtk_header_bar_new ();
	textview = gtk_text_view_new ();
	textbuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
	cb_algorithm = gtk_combo_box_text_new ();
	cb_skip_hidden = gtk_check_button_new_with_label ("Skip hidden files. (leading '.' in file name)");
	cb_full = gtk_check_button_new_with_label ("Ignore index file and make a full backup");
	cb_verbose = gtk_check_button_new_with_label ("Verbose output");
	cb_yes = gtk_check_button_new_with_label ("Answer all questions with yes (script-friendly)"); 
	label1 = gtk_label_new("Command: ");
	label_path = gtk_label_new("Path to generated archive file:");
	label_algorithm = gtk_label_new("Compression algorithm:");
	label_source = gtk_label_new("Path to the directory which should be stored in backup:");
	label_index = gtk_label_new("Path to the index directory:");
	spinner = gtk_spinner_new();
	
	scrolled_window = gtk_scrolled_window_new(NULL,NULL);
	vertical = gtk_box_new (GTK_ORIENTATION_VERTICAL, 15);
	horizontal1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	horizontal2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	horizontal3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	horizontal4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	horizontal5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	horizontal6 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	horizontal7 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	horizontal8 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	horizontal9 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	horizontal10 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	horizontal11 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	horizontal12 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	
	// GTK COMBO BOX
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 0, "id1", "b64encode");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 1, "id2", "bzip2");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 2, "id3", "compress");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 3, "id4", "grzip");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 4, "id5", "gzip");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 5, "id6", "lrzip");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 6, "id7", "lzip");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 7, "id8", "lzop");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 8, "id9", "uuencode");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cb_algorithm), 9, "id10", "xz");
	gtk_combo_box_set_active(GTK_COMBO_BOX(cb_algorithm), 4);
	
	gtk_box_pack_start(GTK_BOX(horizontal1), label_path, TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(horizontal1), button_path, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal2), label_algorithm, TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(horizontal2), cb_algorithm, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal3), label_index, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal3), button_index, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal4), label_source, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal4), button_source, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal5), cb_skip_hidden, TRUE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(horizontal6), cb_full, TRUE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(horizontal7), cb_verbose, TRUE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(horizontal8), cb_yes, TRUE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(horizontal9), label1, TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(horizontal9), textview, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal10), spinner, TRUE, TRUE,0);

	// GTK GRID
	//~ gtk_grid_attach (GTK_GRID (grid), button_path, 2, 0, 1, 1);
	//~ gtk_grid_attach (GTK_GRID (grid), cb_algorithm, 2, 1, 1, 1);
	//~ gtk_grid_attach (GTK_GRID (grid), button_source, 2, 3, 1, 1);
	//~ gtk_grid_attach (GTK_GRID (grid), cb_skip_hidden, 2, 5, 1, 1);
	//~ gtk_grid_attach (GTK_GRID (grid), cb_full, 2, 6, 1, 1);
	//~ gtk_grid_attach (GTK_GRID (grid), cb_verbose, 2, 7, 1, 1);
	//~ gtk_grid_attach (GTK_GRID (grid), cb_yes, 2, 8, 1, 1);
	//~ gtk_grid_attach (GTK_GRID (grid), label1, 1, 9, 1, 1);
	//~ gtk_grid_attach_next_to (GTK_GRID (grid), textview, label1, GTK_POS_RIGHT, 1, 1);
	//~ gtk_grid_attach (GTK_GRID (grid), spinner, 2, 10, 1, 1);
	
	// GTK HEADER BAR
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
	gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);
	gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "Incremental Backup GUI");
	gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header_bar), "a|a|C|C|G");

	//GTK WINDOW
	gtk_window_set_default_size((GTK_WINDOW(window)), 800, 800);

	//GTK TEXT VIEW
	gtk_text_buffer_set_text(textbuffer, "a|C|a|C|a|a|a|C|C|G|", -1);


	//~ gtk_container_add (GTK_CONTAINER (window), grid);
	gtk_container_add (GTK_CONTAINER (window), scrolled_window);
	gtk_container_add (GTK_CONTAINER (scrolled_window), vertical);
	gtk_container_add (GTK_CONTAINER (vertical), horizontal1);
	gtk_container_add (GTK_CONTAINER (vertical), horizontal2);
	gtk_container_add (GTK_CONTAINER (vertical), horizontal3);
	gtk_container_add (GTK_CONTAINER (vertical), horizontal4);
	gtk_container_add (GTK_CONTAINER (vertical), horizontal5);
	gtk_container_add (GTK_CONTAINER (vertical), horizontal6);
	gtk_container_add (GTK_CONTAINER (vertical), horizontal7);
	gtk_container_add (GTK_CONTAINER (vertical), horizontal8);
	gtk_container_add (GTK_CONTAINER (vertical), horizontal9);
	gtk_container_add (GTK_CONTAINER (vertical), horizontal10);

	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	gtk_widget_show_all(window);
	gtk_main();
	
	return 0;
}
