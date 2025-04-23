#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/menus/menus.h"
#include "../../include/user/auth.h"
#include "../../include/user/session.h"
#include "../../include/profile/profile.h"

void show_welcome_page() {
    int choice;

    printf("==================================================\n");
    printf("🔐  SECURE FILE MANAGEMENT SYSTEM\n");
    printf("==================================================\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Exit\n");
    printf("--------------------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            login_user();  // Login function from auth.c
            break;
        case 2:
            register_user();  // Registration function from auth.c
            break;
        case 3:
            printf("Exiting...\n");
            exit(0);  // Exit the program
        default:
            printf("Invalid choice. Please try again.\n");
            show_welcome_page();  // Recursively call the function for invalid input
            break;
    }
}

void show_main_menu(const char *username) {
    int choice;

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
    
    switch(choice) {
        case 1:
            show_file_management_menu();
            break;
        case 2:
            view_profile(username);
            break;
        case 3:
            view_audit_logs();
            break;
        case 4:
            end_session();  // Logout function from session.c
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            show_main_menu(username);
            break;
    }
}

void show_file_management_menu() {
    int choice;

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

    switch(choice) {
        case 1:
            // Optional: Upload file functionality
            break;
        case 2:
            // Optional: Download file functionality
            break;
        case 3:
            // Optional: List files functionality
            break;
        case 4:
            // Optional: Search files functionality
            break;
        case 5:
            // Optional: Delete file functionality
            break;
        case 6:
            // Return to main menu
            show_main_menu("username");  // Use a valid username
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            show_file_management_menu();
            break;
    }
}

void show_search_results(const char *query, const char *results) {
    printf("--------------------------------------------------\n");
    printf("🔍 Search Results for '%s':\n", query);
    printf("%s\n", results);
    printf("--------------------------------------------------\n");
    printf("Select file number for more actions or 0 to return: ");
    int file_choice;
    scanf("%d", &file_choice);

    if (file_choice == 0) {
        show_file_management_menu();
    } else {
        // Optional: Handle file choice actions
    }
}

void show_security_settings_menu() {
    int choice;

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

    switch(choice) {
        case 1:
            // Optional: Change password functionality
            break;
        case 2:
            // Optional: View audit logs functionality
            break;
        case 3:
            // Optional: Enable/Disable 2FA functionality
            break;
        case 4:
            show_main_menu("username");  // Use a valid username
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            show_security_settings_menu();
            break;
    }
}
