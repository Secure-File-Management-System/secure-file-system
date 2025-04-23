#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/file/file_operations.h"
#include "../../include/user/session.h"
#include "../../include/security/logging.h"  // For logging file operations

#define MAX_FILE_NAME_LEN 256
#define MAX_FILE_PATH_LEN 512

// Simulated file storage (in reality, these would be stored in a database or filesystem)
typedef struct File {
    char filename[MAX_FILE_NAME_LEN];
    char owner[MAX_FILE_NAME_LEN];  // User who uploaded the file
    char filepath[MAX_FILE_PATH_LEN];  // Path to the file
    char last_modified[MAX_FILE_NAME_LEN];  // Date of last modification
} File;

File files_db[100];  // Simulated database for storing files (max 100 files)
int file_count = 0;  // Number of files stored

void upload_file() {
    char filename[MAX_FILE_NAME_LEN];
    char filepath[MAX_FILE_PATH_LEN];
    char current_user[MAX_FILE_NAME_LEN];
    const char *user = get_current_user();

    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

    printf("Enter the file name: ");
    scanf("%s", filename);
    printf("Enter the file path: ");
    scanf("%s", filepath);

    // Store the file metadata in the simulated file database
    strcpy(files_db[file_count].filename, filename);
    strcpy(files_db[file_count].owner, user);
    strcpy(files_db[file_count].filepath, filepath);
    strcpy(files_db[file_count].last_modified, "2025-04-21");  // Set a dummy last modified date
    file_count++;  // Increment file count

    printf("File uploaded successfully!\n");

    log_action(get_current_user(), "Uploaded file", filename);  // Log the file upload
}

void download_file() {
    char filename[MAX_FILE_NAME_LEN];
    char current_user[MAX_FILE_NAME_LEN];
    const char *user = get_current_user();

    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

    printf("Enter the file name to download: ");
    scanf("%s", filename);

    // Find the file in the simulated database
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files_db[i].filename, filename) == 0) {
            if (strcmp(files_db[i].owner, user) == 0) {
                printf("File downloaded successfully: %s\n", files_db[i].filepath);
                log_action(get_current_user(), "Downloaded file", filename);  // Log the file download
                return;
            } else {
                printf("You do not have permission to download this file.\n");
                return;
            }
        }
    }

    printf("File not found.\n");
}

void list_files() {
    const char *user = get_current_user();

    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

    printf("Listing files for user: %s\n", user);

    // List all files uploaded by the current user
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files_db[i].owner, user) == 0) {
            printf("[%d] %s  |  Last Modified: %s\n", i + 1, files_db[i].filename, files_db[i].last_modified);
        }
    }
}

void search_files(const char *search_term) {
    printf("Searching for files with term: %s\n", search_term);

    // Search for files in the simulated database
    for (int i = 0; i < file_count; i++) {
        if (strstr(files_db[i].filename, search_term)) {
            printf("[%d] %s  |  Owner: %s  |  Last Modified: %s\n", i + 1, files_db[i].filename, files_db[i].owner, files_db[i].last_modified);
        }
    }
}

void delete_file() {
    char filename[MAX_FILE_NAME_LEN];
    const char *user = get_current_user();

    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

    printf("Enter the file name to delete: ");
    scanf("%s", filename);

    // Find and delete the file from the simulated database
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files_db[i].filename, filename) == 0) {
            if (strcmp(files_db[i].owner, user) == 0) {
                // Shift the remaining files to fill the deleted file's slot
                for (int j = i; j < file_count - 1; j++) {
                    files_db[j] = files_db[j + 1];
                }
                file_count--;  // Decrement the file count
                printf("File deleted successfully!\n");
                log_action(get_current_user(), "Deleted file", filename);  // Log the file deletion
                return;
            } else {
                printf("You do not have permission to delete this file.\n");
                return;
            }
        }
    }

    printf("File not found.\n");
}
