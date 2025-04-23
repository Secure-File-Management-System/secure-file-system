#include <stdio.h>
#include <string.h>
#include "../../include/profile/profile.h"
#include "../../include/user/session.h"
#include "../../include/user/auth.h"  // For password validation and hashing

#define MAX_PASSWORD_LEN 100

void view_profile() {
    const char *user = get_current_user();

    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

    printf("Viewing profile for user: %s\n", user);
    // For now, we will just display the username as part of the profile
    printf("Username: %s\n", user);
    // Add more profile details as needed
}

void change_password() {
    const char *user = get_current_user();

    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

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
