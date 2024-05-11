#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_GROUPS 50
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_GROUP_NAME_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char groups[MAX_GROUPS][MAX_GROUP_NAME_LENGTH];
    int num_groups;
    char password_expiration[MAX_PASSWORD_LENGTH];
} User;

User users[MAX_USERS];
int num_users = 0;

void add_user(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    GtkWidget *grid;
    GtkWidget *username_label;
    GtkWidget *username_entry;
    GtkWidget *password_label;
    GtkWidget *password_entry;
    gchar *username;
    gchar *password;

    dialog = gtk_dialog_new_with_buttons("Add User", GTK_WINDOW(data),
                                         GTK_DIALOG_MODAL,
                                         "OK", GTK_RESPONSE_OK,
                                         "Cancel", GTK_RESPONSE_CANCEL,
                                         NULL);

    grid = gtk_grid_new();
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), grid);

    username_label = gtk_label_new("Username:");
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);

    username_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), username_entry, 1, 0, 1, 1);

    password_label = gtk_label_new("Password:");
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);

    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 1, 1, 1);

    gtk_widget_show_all(dialog);

    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_OK) {
        username = gtk_entry_get_text(GTK_ENTRY(username_entry));
        password = gtk_entry_get_text(GTK_ENTRY(password_entry));
        // Add user
        printf("Adding user: %s, %s\n", username, password);
    }

    gtk_widget_destroy(dialog);
}

void delete_user(GtkWidget *widget, gpointer data) {
    // Implementation for delete user dialog
}

void display_users(GtkWidget *widget, gpointer data) {
    // Implementation for displaying users dialog
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *add_user_button;
    GtkWidget *delete_user_button;
    GtkWidget *display_users_button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "User Manager");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    add_user_button = gtk_button_new_with_label("Add User");
    g_signal_connect(add_user_button, "clicked", G_CALLBACK(add_user), window);
    gtk_grid_attach(GTK_GRID(grid), add_user_button, 0, 0, 1, 1);

    delete_user_button = gtk_button_new_with_label("Delete User");
    g_signal_connect(delete_user_button, "clicked", G_CALLBACK(delete_user), window);
    gtk_grid_attach(GTK_GRID(grid), delete_user_button, 1, 0, 1, 1);

    display_users_button = gtk_button_new_with_label("Display Users");
    g_signal_connect(display_users_button, "clicked", G_CALLBACK(display_users), window);
    gtk_grid_attach(GTK_GRID(grid), display_users_button, 0, 1, 2, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
