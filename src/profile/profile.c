#include <stdio.h>
#include <string.h>
#include "../../include/profile/profile.h"
#include "../../include/menus/menus.h" 
#include "../../include/user/session.h"
#include "../../include/user/auth.h"
#include "../../include/security/logging.h"  // For logging actions

#define MAX_PASSWORD_LEN 100

// Function to view the profile of the currently logged-in user
void view_profile() {
    const char *user = get_current_user();  // Get the current logged-in user

    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

    printf("Viewing profile for user: %s\n", user);
    printf("Username: %s\n", user);

    // Call the change password menu directly after viewing the profile
    show_security_settings_menu(user);  // This will lead to the password change menu
}


// Function to change the password of the currently logged-in user
void change_password() {
    const char *user = get_current_user();  // Get the current logged-in user

    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

    char password[MAX_PASSWORD_LEN];  // Current password
    char new_password[MAX_PASSWORD_LEN];
    char confirm_password[MAX_PASSWORD_LEN];

    // Prompt user for current password
    printf("Enter current password: ");
    scanf("%s", password);

    // Verify that the current password matches
    if (!validate_password( password)) {  // Replace verify_password with validate_password
        printf("❌ Incorrect password.\n");
        return;
    }

    // Prompt user for new password
    printf("Enter new password: ");
    scanf("%s", new_password);
    printf("Confirm new password: ");
    scanf("%s", confirm_password);

    // Check if the new passwords match
    if (strcmp(new_password, confirm_password) != 0) {
        printf("❌ New passwords do not match.\n");
        return;
    }

    // Update the password in the system
    if (update_user_password(user, new_password)) {
        printf("✅ Password changed successfully!\n");
        log_action(user, "Password changed", "N/A");  // Log the action (You can adjust the target as needed)
    } else {
        printf("❌ Failed to change password.\n");
    }
}