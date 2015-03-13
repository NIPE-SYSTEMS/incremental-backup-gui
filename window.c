#define UNUSED(x) (void)(x)

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <glib/gi18n.h>

GtkWidget *window;
GtkWidget *grid;
GtkWidget *button_path;
GtkWidget *header_bar;
GtkWidget *textview;
GtkTextBuffer *textbuffer;

int main()
{
	gtk_init (NULL, NULL);
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	grid = gtk_grid_new ();
	button_path = gtk_file_chooser_button_new (_("Select a directory"), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER (button_path), "/home/");
	header_bar = gtk_header_bar_new ();
	textview = gtk_text_view_new ();
	textbuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));

	gtk_grid_attach (GTK_GRID (grid), button_path, 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), textview, 0, 7, 1, 1);


	// GTK HEADER BAR
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
	gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);
	gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "Incremental Backup GUI");
	gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header_bar), "a|a|C|C|G");

	//GTK TEXT VIEW
	gtk_text_buffer_set_text(textbuffer, "a|C|a|C|a|a|a|C|C|G|", -1);


	gtk_container_add (GTK_CONTAINER (window), grid);
	gtk_container_add(GTK_CONTAINER(window), textview);

	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	gtk_widget_show_all(window);
	gtk_main();
	
	return 0;
}
