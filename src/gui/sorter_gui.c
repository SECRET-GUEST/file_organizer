#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h> 
#include <string.h> 

#include "gui/sorter_gui.h"
#include "program/sorter.h"
#include "../translate/translator.h"
#include "handlers/error_handler.h"



static char *inputDirectory = NULL;
static char *outputDirectory = NULL;

// Prototypes des fonctions
static void on_select_input_directory(GtkWidget *button, gpointer user_data);
static void on_run_sorter(GtkWidget *button, gpointer user_data);


void run_gui(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), translate("sorter_gui.txt1"));  // File Sorter
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE); // Avoid resizing of the window
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Set some style to the window
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "window { border-radius: 0px; }",
                                    -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                               GTK_STYLE_PROVIDER(provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);

    // Vertical box to hold the label and the buttons
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10); // Add some border space
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Label to describe the program functionality
    GtkWidget *label = gtk_label_new(translate("sorter_gui.txt17")); // This program sorts your files based on their extensions.
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    // Vertical box to hold only the buttons, centered in the middle of the window
    GtkWidget *button_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); // Increased spacing between buttons
    gtk_box_pack_start(GTK_BOX(vbox), button_vbox, TRUE, FALSE, 0);

    GtkWidget *buttonInput = gtk_button_new_with_label(translate("sorter_gui.txt2")); // Select Input Directory
    g_signal_connect(buttonInput, "clicked", G_CALLBACK(on_select_input_directory), NULL);
    gtk_box_pack_start(GTK_BOX(button_vbox), buttonInput, TRUE, TRUE, 0);

    GtkWidget *buttonRun = gtk_button_new_with_label(translate("sorter_gui.txt3")); // Run sorter
    g_signal_connect(buttonRun, "clicked", G_CALLBACK(on_run_sorter), NULL);
    gtk_box_pack_start(GTK_BOX(button_vbox), buttonRun, TRUE, TRUE, 0);

    gtk_widget_show_all(window);
    gtk_main();
}


static void on_select_input_directory(GtkWidget *button, gpointer user_data) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Select Input Directory", NULL, GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, "_Cancel", GTK_RESPONSE_CANCEL, "_Select", GTK_RESPONSE_ACCEPT, NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        inputDirectory = g_strdup(filename);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

static void on_run_sorter(GtkWidget *button, gpointer user_data) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Select Output Directory", NULL, GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, "_Cancel", GTK_RESPONSE_CANCEL, "_Select", GTK_RESPONSE_ACCEPT, NULL);

 
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        outputDirectory = g_strdup(filename);
        g_free(filename);
        
        if (strcmp(inputDirectory, outputDirectory) == 0) {
            display_error_message(translate("sorter_gui.txt18")); // Input and Output directories are identical
            gtk_widget_destroy(dialog);
            return;
        }
        
        char *outputDirCopy = strdup(outputDirectory);
        if (!outputDirCopy) {
            display_error_message(translate("sorter_gui.txt19")); // Memory Allocation Error
            gtk_widget_destroy(dialog);
            return;
        }
        
        char *outputDirParent = outputDirCopy; // Initialize to outputDirCopy
        
        while (strcmp(outputDirParent, ".") != 0 && strcmp(outputDirParent, "/") != 0) {
            outputDirParent = dirname(outputDirParent); // Get the parent directory of outputDirectory
            
            if (strcmp(outputDirParent, inputDirectory) == 0) {
                display_error_message(translate("sorter_gui.txt20")); // The output directory is a subdirectory of the input directory
                free(outputDirCopy);
                gtk_widget_destroy(dialog);
                return;
            }
        }
        
        free(outputDirCopy);
    } else {
        display_error_message(translate("sorter_gui.txt4")); // Please choose a correct output directory
        gtk_widget_destroy(dialog);
        return;
    }
    
    gtk_widget_destroy(dialog);
    
    if (initialize_sorter(inputDirectory, outputDirectory) == -1) {
        display_error_message(translate("sorter_gui.txt5")); // An error occurred during file sorting.
    }
}

