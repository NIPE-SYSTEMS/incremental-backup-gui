#define UNUSED(x) (void)(x)
#define COMMAND_LEN 50
#define DATA_SIZE 512

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

GtkWidget *window;
GtkWidget *button_path;
GtkWidget *button_source;
GtkWidget *button_index;
GtkWidget *header_bar;
GtkWidget *command_entry;
GtkWidget *cb_algorithm;
GtkWidget *cb_skip_hidden;
GtkWidget *cb_full;
GtkWidget *cb_yes;
GtkWidget *cb_stats;
//GtkWidget *label1;
GtkWidget *label_path;
GtkWidget *label_algorithm;
GtkWidget *label_source;
GtkWidget *label_index;
GtkWidget *label2;
GtkWidget *spinner;
GtkWidget *startba;
GtkSizeGroup *sizegroup1;
GtkSizeGroup *sizegroup2;
GtkSizeGroup *sizegroup3;
GtkWidget *space;

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
GtkWidget *horizontal13;

FILE *pf;
char command[COMMAND_LEN];
char data[DATA_SIZE];

FILE *version;
char command_version[COMMAND_LEN];
char data_version[DATA_SIZE];

int main()
{
	gtk_init (NULL, NULL);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	
	button_path = gtk_file_chooser_button_new("Select a directory", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	button_source = gtk_file_chooser_button_new("Select a directory", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	button_index = gtk_file_chooser_button_new("Select a directory", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(button_path), "/home/");
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(button_source), "/");
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(button_source), "/home/");
	header_bar = gtk_header_bar_new ();
	command_entry = gtk_entry_new();
	cb_algorithm = gtk_combo_box_text_new ();
	cb_skip_hidden = gtk_check_button_new_with_label("Skip hidden files. (leading '.' in file name)");
	cb_full = gtk_check_button_new_with_label("Ignore index file and make a full backup");
	cb_yes = gtk_check_button_new_with_label("Answer all questions with yes (script-friendly)"); 
	cb_stats = gtk_check_button_new_with_label("Show stats at the end");
	//label1 = gtk_label_new("Command: ");
	label2 = gtk_label_new("'-v' = verbose (REQUIRED)");
	label_path = gtk_label_new("Path to generated archive file:");
	label_algorithm = gtk_label_new("Compression algorithm:");
	label_source = gtk_label_new("Path to the directory which should be backupeds:");
	label_index = gtk_label_new("Path to the index directory:");
	space = gtk_label_new("");
	spinner = gtk_spinner_new();
	startba = gtk_button_new_with_label("Backup!");
	sizegroup1 = gtk_size_group_new(GTK_SIZE_GROUP_HORIZONTAL);
	sizegroup2 = gtk_size_group_new(GTK_SIZE_GROUP_HORIZONTAL);
	sizegroup3 = gtk_size_group_new(GTK_SIZE_GROUP_HORIZONTAL);
	
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
	horizontal13 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

	// GTK SIZE GROUP
	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup1), label_path);
	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup1), label_algorithm);
	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup1), label_index);
	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup1), label_source);
	//gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup1), label1);
	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup1), command_entry);

	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup2), cb_skip_hidden);
	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup2), cb_full);
	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup2), cb_yes);
	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup2), cb_stats);
	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup2), label2);

	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup3), button_path);
	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup3), cb_algorithm);
	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup3), button_index);
	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup3), button_source);
	gtk_size_group_add_widget(GTK_SIZE_GROUP(sizegroup3), startba);

	
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
	
	// GTK BOX
	gtk_box_pack_start(GTK_BOX(horizontal1), label_path, TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(horizontal1), button_path, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal2), label_algorithm, TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(horizontal2), cb_algorithm, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal3), label_index, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal3), button_index, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal4), label_source, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal4), button_source, TRUE, TRUE,30);
	// gtk_box_pack_start(GTK_BOX(horizontal5), space, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal6), cb_skip_hidden, TRUE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(horizontal7), cb_full, TRUE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(horizontal8), cb_yes, TRUE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(horizontal9), cb_stats, TRUE, FALSE,0);
	// gtk_box_pack_start(GTK_BOX(horizontal10), space, TRUE, FALSE,0);
	//gtk_box_pack_start(GTK_BOX(horizontal9), label1, TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(horizontal11), command_entry, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal11), startba, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal12), label2, TRUE, TRUE,30);
	gtk_box_pack_start(GTK_BOX(horizontal13), spinner, TRUE, TRUE,0);
	
	sprintf(command_version, "~/incremental-backup/bin/incremental-backup -V");
	version = popen(command_version, "r");
	fgets(data_version, DATA_SIZE, version);
	data_version[strlen(data_version) - 1] = '\0'; // remove trailing newline
	fprintf(stdout, "'%s'\n", data_version);
	pclose(version);

	// GTK HEADER BAR
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
	gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);
	gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "Incremental Backup GUI");
	// gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header_bar), "a|a|C|C|G");
	gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header_bar), data_version);

	//GTK WINDOW
	gtk_window_set_default_size((GTK_WINDOW(window)), 800, 800);

	//GTK ENTRY
	gtk_entry_set_placeholder_text(GTK_ENTRY(command_entry), "Command");

	// GTK LABEL
	gtk_widget_set_halign(label_path, GTK_ALIGN_START);
	gtk_widget_set_halign(label_algorithm, GTK_ALIGN_START);
	gtk_widget_set_halign(label_index, GTK_ALIGN_START);
	gtk_widget_set_halign(label_source, GTK_ALIGN_START);

	gtk_container_add (GTK_CONTAINER(window), scrolled_window);
	gtk_container_add (GTK_CONTAINER(scrolled_window), vertical);
	gtk_box_pack_start(GTK_BOX(vertical), horizontal1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vertical), horizontal2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vertical), horizontal3, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vertical), horizontal4, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vertical), horizontal5, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vertical), horizontal6, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vertical), horizontal7, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vertical), horizontal8, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vertical), horizontal9, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vertical), horizontal10, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vertical), horizontal11, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vertical), horizontal12, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vertical), horizontal13, FALSE, FALSE, 0);
	
	gtk_container_set_border_width(GTK_CONTAINER(vertical),15);

	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	// POPEN
	// sprintf(command, "~/incremental-backup/bin/incremental-backup --help");
	// pf = popen(command,"w");
 //    fgets(data, DATA_SIZE , pf);
 //    fprintf(stdout, "%s\n",data);
	// pclose(pf);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
