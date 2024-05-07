#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void add_user(const char *username) {
    char command[100];
    snprintf(command, sizeof(command), "sudo useradd %s", username);
    system(command);
}

void delete_user(const char *username) {
    char command[100];
    snprintf(command, sizeof(command), "sudo userdel -r %s", username);
    system(command);
}

void add_group(const char *groupname) {
    char command[100];
    snprintf(command, sizeof(command), "sudo groupadd %s", groupname);
    system(command);
}

void delete_group(const char *groupname) {
    char command[100];
    snprintf(command, sizeof(command), "sudo groupdel %s", groupname);
    system(command);
}

void change_user_info(const char *username, const char *new_info) {
    char command[100];
    snprintf(command, sizeof(command), "sudo usermod -c '%s' %s", new_info, username);
    system(command);
}

void change_account_info(const char *username, const char *expiration_date) {
    char command[100];
    snprintf(command, sizeof(command), "sudo chage -E %s %s", expiration_date, username);
    system(command);
}

void assign_user_to_group(const char *username, const char *groupname) {
    char command[100];
    snprintf(command, sizeof(command), "sudo usermod -a -G %s %s", groupname, username);
    system(command);
}

int main() {
    system("pwd");
    system("pwd");
    system("pwd");
    system("pwd");
    int choice;
    char username[50], groupname[50], new_info[100], expiration_date[20];
    do {
        printf("\nUser Manager Menu\n");
        printf("1. Add user\n");
        printf("2. Delete user\n");
        printf("3. Add group\n");
        printf("4. Delete group\n");
        printf("5. Change user information\n");
        printf("6. Change account information\n");
        printf("7. Assign user to group\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username to add: ");
                scanf("%s", username);
                add_user(username);
                break;
            case 2:
                printf("Enter username to delete: ");
                scanf("%s", username);
                delete_user(username);
                break;
            case 3:
                printf("Enter group name to add: ");
                scanf("%s", groupname);
                add_group(groupname);
                break;
            case 4:
                printf("Enter group name to delete: ");
                scanf("%s", groupname);
                delete_group(groupname);
                break;
            case 5:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter new information: ");
                scanf(" %[^\n]", new_info);
                change_user_info(username, new_info);
                break;
            case 6:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter expiration date (YYYY-MM-DD): ");
                scanf("%s", expiration_date);
                change_account_info(username, expiration_date);
                break;
            case 7:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter group name: ");
                scanf("%s", groupname);
                assign_user_to_group(username, groupname);
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 8);

    return 0;
}
