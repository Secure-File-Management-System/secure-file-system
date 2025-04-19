// logging.c - Logs user activity to audit.log

#include <stdio.h>
#include <time.h>
#include "logging.h"

#define LOG_FILE "audit.log"

void log_action(const char *username, const char *action, const char *target) {
    FILE *log = fopen(LOG_FILE, "a");
    if (!log) {
        perror("Unable to open log file");
        return;
    }

    // Get current time
    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    if (timestamp) {
        timestamp[strcspn(timestamp, "\n")] = '\0';  // Remove newline
    }

    // Format: [timestamp] user performed action on target
    fprintf(log, "[%s] %s performed '%s' on '%s'\n", timestamp, username, action, target);
    fclose(log);
}

void view_log() {
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
