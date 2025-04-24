#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/menus/menus.h"
#include "../../include/user/auth.h"
#include "../../include/user/session.h"
#include "../../include/profile/profile.h"
#include "../../include/security/logging.h"
#include "../../include/file/file_operations.h"

void show_welcome_page() {
    int choice;

    while (1) {
        printf("==================================================\n");
        printf("🔐  SECURE FILE MANAGEMENT SYSTEM\n");
        printf("==================================================\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("--------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login_user();  // This should call show_main_menu() upon success
                break;
            case 2:
                register_user();  // This can return to welcome menu after registration
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void show_main_menu(const char *username) {
    int choice;

    while (1) {
        printf("==================================================\n");
        printf("👋 Welcome, %s\n", username);
        printf("--------------------------------------------------\n");
        printf("1. Manage Files\n");
        printf("2. View Profile\n");
        printf("3. Audit Logs\n");
        printf("4. Logout\n");
        printf("--------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                show_file_management_menu(username);
                break;
            case 2:
                view_profile(username);
                break;
            case 3:
                view_audit_logs(username);
                break;
            case 4:
                end_session();
                return;  // Exit main menu and go back to welcome
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void show_file_management_menu(const char *username) {
    int choice;

    while (1) {
        printf("==================================================\n");
        printf("📂 FILE MANAGEMENT\n");
        printf("--------------------------------------------------\n");
        printf("1. Upload File\n");
        printf("2. Download File\n");
        printf("3. List My Files\n");
        printf("4. Search Files\n");
        printf("5. Delete File\n");
        printf("6. Back to Main Menu\n");
        printf("--------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                upload_file(username);
                break;
            case 2:
                download_file(username);
                break;
            case 3:
                list_files(username);
                break;
            case 4:
                search_files(username);
                break;
            case 5:
                delete_file(username);
                break;
            case 6:
                return;  // Return to main menu
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void show_search_results(const char *query, const char *results, const char *username) {
    printf("--------------------------------------------------\n");
    printf("🔍 Search Results for '%s':\n", query);
    printf("%s\n", results);
    printf("--------------------------------------------------\n");
    printf("Select file number for more actions or 0 to return: ");
    int file_choice;
    scanf("%d", &file_choice);

    if (file_choice == 0) {
        show_file_management_menu(username);
    } else {
        // Implement action on file selection if needed
    }
}

void show_security_settings_menu(const char *username) {
    int choice;

    while (1) {
        printf("==================================================\n");
        printf("🛡️ SECURITY SETTINGS\n");
        printf("--------------------------------------------------\n");
        printf("1. Change Password\n");
        printf("2. View Audit Logs\n");
        printf("3. Enable/Disable 2FA (if implemented)\n");
        printf("4. Back to Main Menu\n");
        printf("--------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                change_password(username);
                break;
            case 2:
                view_audit_logs(username);
                break;
            case 3:
                printf("2FA toggle not implemented yet.\n");
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
