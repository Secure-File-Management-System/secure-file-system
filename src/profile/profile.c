#include <stdio.h>
#include <string.h>
#include "../../include/profile/profile.h"
<<<<<<< HEAD
#include "../../include/menus/menus.h" 
#include "../../include/user/session.h"
#include "../../include/user/auth.h"
#include "../../include/security/logging.h"  // For logging actions

#define MAX_PASSWORD_LEN 100

// Function to view the profile of the currently logged-in user
void view_profile() {
    const char *user = get_current_user();  // Get the current logged-in user
=======
#include "../../include/user/session.h"
#include "../../include/user/auth.h"  // For password validation and hashing

#define MAX_PASSWORD_LEN 100

void view_profile() {
    const char *user = get_current_user();
>>>>>>> 3ad65e5 (updated system)

    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

    printf("Viewing profile for user: %s\n", user);
<<<<<<< HEAD
    printf("Username: %s\n", user);

    // Call the change password menu directly after viewing the profile
    show_security_settings_menu(user);  // This will lead to the password change menu
}


// Function to change the password of the currently logged-in user
void change_password() {
    const char *user = get_current_user();  // Get the current logged-in user
=======
    // For now, we will just display the username as part of the profile
    printf("Username: %s\n", user);
    // Add more profile details as needed
}

void change_password() {
    const char *user = get_current_user();
>>>>>>> 3ad65e5 (updated system)

    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

<<<<<<< HEAD
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
=======
    char old_password[MAX_PASSWORD_LEN];
    char new_password[MAX_PASSWORD_LEN];
    char confirm_password[MAX_PASSWORD_LEN];

    printf("Enter current password: ");
    scanf("%s", old_password);

    // Validate the old password (only the password needs validation now)
    if (validate_password(old_password)) {
        printf("Enter new password: ");
        scanf("%s", new_password);

        printf("Confirm new password: ");
        scanf("%s", confirm_password);

        if (strcmp(new_password, confirm_password) == 0) {
            // Here we would save the new password hash to storage
            // For now, just simulate it with a success message
            printf("Password changed successfully!\n");

            // Update the password (this is where you would actually implement saving the new hash)
            // For now, simulate this process.
            update_password_hash(user, new_password);  // This function should be implemented in auth.c

        } else {
            printf("New passwords do not match.\n");
        }
    } else {
        printf("Incorrect current password.\n");
    }
}
>>>>>>> 3ad65e5 (updated system)
