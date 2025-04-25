#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/user/session.h"
#include "../../include/security/logging.h"  // For logging session events

#define MAX_USERNAME_LEN 100

static char current_user[MAX_USERNAME_LEN] = "";  // Stores the current logged-in user's username

void start_session(const char *username) {
    // Start the session by storing the current user's username
    strncpy(current_user, username, MAX_USERNAME_LEN);
    current_user[MAX_USERNAME_LEN - 1] = '\0';  // Ensure null-termination

    printf("Session started for user: %s\n", username);
    log_action(username, "Session started", "system"); // Log session start
}

void end_session() {
    if (strlen(current_user) > 0) {
        printf("Logging out user: %s\n", current_user);
        log_action(current_user, "Session ended", "system");  // Log session end
        memset(current_user, 0, sizeof(current_user));  // Clear current user data
    }
}

const char *get_current_user() {
    return (strlen(current_user) > 0) ? current_user : NULL;
}

