// main.c - Centralized CLI Control Flow

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/menus/menus.h"
#include "../include/user/auth.h"
#include "../include/user/session.h"
#include "../include/file/file_operations.h"
#include "../include/security/logging.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void clear_input_buffer() {
    while (getchar() != '\n'); // Clear the buffer
}

int main() {
    int choice;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 0c670fe (complete working system)
    load_files_metadata();

    while (1) {
        show_welcome_page();
        printf("\n1. Login\n2. Register\n3. View Audit Log\n4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter username: ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = 0;

=======
    while (1) {
        show_welcome_page();
        printf("\n1. Login\n2. Register\n3. View Audit Log\n4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter username: ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = 0;

>>>>>>> 3ad65e5 (updated system)
                printf("Enter password: ");
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = 0;

                if (validate_user_credentials(username, password)) {
                    start_session(username);
                    log_action(username, "Login", "System");
                    show_main_menu(username);
                    end_session(username);
                } else {
                    printf("Invalid username or password.\n");
                }
                break;

            case 2:
                printf("Enter username: ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = 0;

                if (is_user_exists(username)) {
                    printf("User already exists.\n");
                    break;
                }

                printf("Enter password: ");
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = 0;

<<<<<<< HEAD
<<<<<<< HEAD
                register_user(); 
=======
                register_user();  // Uses interactive function in auth.c
>>>>>>> 3ad65e5 (updated system)
=======
                register_user(); 
>>>>>>> 0c670fe (complete working system)
                break;

            case 3:
                view_audit_logs();
                break;

            case 4:
                printf("Goodbye!\n");
                exit(0);

            default:
                printf("Invalid option.\n");
        }
    }

    return 0;
}