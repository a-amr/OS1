#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void add_user(const char *username) {
    char command[100];
    snprintf(command, sizeof(command), "sudo useradd -m %s", username);
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
void change_aging_info(const char *username) {
    char command[100];
    snprintf(command, sizeof(command), "sudo chage   %s", username);
    system(command);
}

void assign_user_to_group(const char *username, const char *groupname) {
    char command[100];
    snprintf(command, sizeof(command), "sudo usermod -a -G %s %s", groupname, username);
    system(command);
}

void change_username(const char *newname, const char *username) {
    char command[100];
    snprintf(command, sizeof(command),"sudo usermod -l %s %s", newname, username);
    system(command);
}

void change_password(const char *username ) {
    char command[100];
    snprintf(command, sizeof(command), "sudo passwd %s\n ", username);
    system(command);
}
void change_home(const char *username, const char *newhome) {
    char command[100];
    snprintf(command, sizeof(command), "sudo usermod -d %s %s",newhome, username);
    system(command);
}
void change_shell(const char *username) {
    char command[100];
    snprintf(command, sizeof(command), "sudo chsh %s",username);
    system(command);
}

int main() {
    int choice;
    char home[50],newuser[50],username[50], groupname[50], new_info[100], expiration_date[20];
    do {
        printf("\nUser Manager Menu\n");
        printf(" 1.Add user\n");
        printf(" 2.Delete user\n");
        printf(" 3.Add group\n");
        printf(" 4.Delete group\n");
        printf(" 5.Change user additional information\n");
        printf(" 6.Change password expiration date for user \n");
        printf(" 7.Change all aging info for user \n");
        printf(" 8.Assign user to group\n");
        printf(" 9.Change user name\n");
        printf("10.change password for user\n");
        printf("11.change home dir for a user\n");
        printf("12.change login shell for user\n");
        printf("13.Exit\n");
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
                change_aging_info(username);
                break;
            case 8:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter group name: ");
                scanf("%s", groupname);
                assign_user_to_group(username, groupname);
                break;
            case 9:
                printf("enter old username: ");
                scanf("%s", username);
                printf("enter new username: ");
                scanf("%s", newuser);
                change_username(newuser, username);
                break;
            case 10:
                printf("enter username to change his password: ");
                scanf("%s", username);
                change_password(username);
                break;
            case 11:
                printf("enter username to change his home dir: ");
                scanf("%s", username);
                printf("enter new home location: ");
                scanf("%s", home);
                change_home(username, home);
                break;
            case 12:
                printf("enter username to chagne his shell: ");
                scanf("%s",username);
                change_shell(username);
                break;
            case 13:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
                //choice =0;
                return 1;
        }
    } while (choice != 13);

    return 0;
}
//feature to add 
//changing group name with groupmod -n newgroup oldgroup
//deleting dir after deliting its user account
