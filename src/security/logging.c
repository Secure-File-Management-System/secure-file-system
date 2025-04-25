#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../../include/security/logging.h"

#define LOG_FILE "audit.log"

// Function to log user actions with more detail
void log_action(const char *username, const char *action, const char *target) {
    FILE *log = fopen(LOG_FILE, "a");
    if (!log) {
        // Enhanced error handling for file opening
        perror("Unable to open log file");
        return;
    }

    // Get current time
    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    if (timestamp) {
        timestamp[strcspn(timestamp, "\n")] = '\0';  // Remove newline from timestamp
    }

    // Format: [timestamp] user performed action on target
    if (target == NULL) {
        // If no target provided (e.g., for login or logout actions)
        fprintf(log, "[%s] %s performed '%s'\n", timestamp, username, action);
    } else {
        // Log actions with a specified target (e.g., file upload or download)
        fprintf(log, "[%s] %s performed '%s' on '%s'\n", timestamp, username, action, target);
    }

    fclose(log);
}

// Function to view the audit logs
void view_audit_logs() {
    FILE *log = fopen(LOG_FILE, "r");
    if (!log) {
        printf("No log file found or unable to open.\n");
        return;
    }

    printf("\n===== Audit Log =====\n");
    char line[256];
    while (fgets(line, sizeof(line), log)) {
        printf("%s", line);
    }
    printf("=====================\n\n");

    fclose(log);
}
