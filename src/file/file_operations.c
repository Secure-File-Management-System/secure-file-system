#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../../include/file/file_operations.h"
#include "../../include/user/session.h"
#include "../../include/security/logging.h"

File files_db[100];  // Define file database
int file_count = 0;  // Define file counter
#define META_FILE "files_meta.db"


void save_files_metadata() {
    FILE *fp = fopen(META_FILE, "wb");
    if (!fp) return;
    fwrite(&file_count, sizeof(int), 1, fp);
    fwrite(files_db, sizeof(File), file_count, fp);
    fclose(fp);
}

void load_files_metadata() {
    FILE *fp = fopen(META_FILE, "rb");
    if (!fp) return;
    fread(&file_count, sizeof(int), 1, fp);
    fread(files_db, sizeof(File), file_count, fp);
    fclose(fp);
}

void upload_file() {
    const char *upload_dir = "to_upload";
    const char *storage_root = "storage";
    const char *user = get_current_user();

    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

    DIR *dir = opendir(upload_dir);
    if (!dir) {
        printf("Failed to open upload directory.\n");
        return;
    }

    struct dirent *entry;
    char files[100][MAX_FILE_NAME_LEN];
    int count = 0;

    printf("Files available for upload:\n");
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            printf("[%d] %s\n", count + 1, entry->d_name);
            strncpy(files[count], entry->d_name, MAX_FILE_NAME_LEN - 1);
            files[count][MAX_FILE_NAME_LEN - 1] = '\0';
            count++;
        }
    }
    closedir(dir);

    if (count == 0) {
        printf("No files found in 'to_upload' folder.\n");
        return;
    }

    int choice;
    printf("Enter the number of the file to upload: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > count) {
        printf("Invalid selection.\n");
        return;
    }

    char selected_file[MAX_FILE_NAME_LEN];
    strncpy(selected_file, files[choice - 1], MAX_FILE_NAME_LEN - 1);
    selected_file[MAX_FILE_NAME_LEN - 1] = '\0';

    char src_path[MAX_FILE_PATH_LEN];
    if (snprintf(src_path, sizeof(src_path), "%s/%s", upload_dir, selected_file) >= sizeof(src_path)) {
        printf("Source path too long. Upload aborted.\n");
        return;
    }

    char user_dir[MAX_FILE_PATH_LEN];
    if (snprintf(user_dir, sizeof(user_dir), "%s/%s", storage_root, user) >= sizeof(user_dir)) {
        printf("User directory path too long. Upload aborted.\n");
        return;
    }

    if (mkdir(user_dir, 0700) != 0 && errno != EEXIST) {
        printf("Failed to create user directory: %s\n", user_dir);
        return;
    }

    char dest_path[MAX_FILE_PATH_LEN];
    if (snprintf(dest_path, sizeof(dest_path), "%s/%s", user_dir, selected_file) >= sizeof(dest_path)) {
        printf("Destination path too long. Upload aborted.\n");
        return;
    }

    FILE *src = fopen(src_path, "rb");
    FILE *dest = fopen(dest_path, "wb");
    if (!src || !dest) {
        printf("Failed to open source or destination file.\n");
        if (src) fclose(src);
        if (dest) fclose(dest);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);

    if (unlink(src_path) == 0) {
        printf("File uploaded and removed from 'to_upload': %s\n", selected_file);
    } else {
        printf("File uploaded but failed to delete from 'to_upload'.\n");
    }

    strncpy(files_db[file_count].filename, selected_file, MAX_FILE_NAME_LEN - 1);
    files_db[file_count].filename[MAX_FILE_NAME_LEN - 1] = '\0';
    strncpy(files_db[file_count].owner, user, MAX_FILE_NAME_LEN - 1);
    files_db[file_count].owner[MAX_FILE_NAME_LEN - 1] = '\0';
    strncpy(files_db[file_count].filepath, dest_path, MAX_FILE_PATH_LEN - 1);
    files_db[file_count].filepath[MAX_FILE_PATH_LEN - 1] = '\0';
    strncpy(files_db[file_count].last_modified, "2025-04-24", 19);
    file_count++;

    log_action(user, "Uploaded file", selected_file);

    // Save file metadata to disk
    save_files_metadata();
}

void download_file() {
    const char *user = get_current_user();

    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

    int user_file_indexes[100];
    int user_file_count = 0;

    printf("Your available files for download:\n");
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files_db[i].owner, user) == 0) {
            user_file_indexes[user_file_count] = i;
            printf("[%d] %s (Last Modified: %s)\n", user_file_count + 1,
                   files_db[i].filename, files_db[i].last_modified);
            user_file_count++;
        }
    }

    if (user_file_count == 0) {
        printf("You have no files available for download.\n");
        return;
    }

    int choice;
    printf("Enter the number of the file to download: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > user_file_count) {
        printf("Invalid selection.\n");
        return;
    }

    int index = user_file_indexes[choice - 1];
    const char *source_path = files_db[index].filepath;
    const char *filename = files_db[index].filename;

    // Create downloads directory if not exists
    const char *download_dir = "downloads";
    if (mkdir(download_dir, 0700) != 0 && errno != EEXIST) {
        printf("Failed to create downloads directory.\n");
        return;
    }

    char dest_path[MAX_FILE_PATH_LEN];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", download_dir, filename);

    FILE *src = fopen(source_path, "rb");
    FILE *dest = fopen(dest_path, "wb");

    if (!src || !dest) {
        printf("Failed to open source or destination file.\n");
        if (src) fclose(src);
        if (dest) fclose(dest);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File downloaded to: %s\n", dest_path);
    log_action(user, "Downloaded file", filename);
}


void list_files() {
    const char *user = get_current_user();

    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

    printf("Listing files for user: %s\n", user);
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files_db[i].owner, user) == 0) {
            printf("[%d] %s  |  Last Modified: %s\n", i + 1, files_db[i].filename, files_db[i].last_modified);
        }
    }
}

void search_files(const char *search_term) {
    const char *user = get_current_user();

    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

    int matched_indexes[100];
    int match_count = 0;

    printf("Search results for \"%s\":\n", search_term);
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files_db[i].owner, user) == 0 &&
            strstr(files_db[i].filename, search_term)) {
            matched_indexes[match_count] = i;
            printf("[%d] %s (Last Modified: %s)\n",
                   match_count + 1,
                   files_db[i].filename,
                   files_db[i].last_modified);
            match_count++;
        }
    }

    if (match_count == 0) {
        printf("No matching files found.\n");
        return;
    }

    char choice;
    printf("Do you want to download one of these files? (y/n): ");
    scanf(" %c", &choice);
    if (choice != 'y' && choice != 'Y') return;

    int selection;
    printf("Enter the number of the file to download: ");
    scanf("%d", &selection);
    if (selection < 1 || selection > match_count) {
        printf("Invalid selection.\n");
        return;
    }

    int index = matched_indexes[selection - 1];
    const char *source_path = files_db[index].filepath;
    const char *filename = files_db[index].filename;

    // Ensure downloads directory exists
    const char *download_dir = "downloads";
    if (mkdir(download_dir, 0700) != 0 && errno != EEXIST) {
        printf("Failed to create downloads directory.\n");
        return;
    }

    char dest_path[MAX_FILE_PATH_LEN];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", download_dir, filename);

    FILE *src = fopen(source_path, "rb");
    FILE *dest = fopen(dest_path, "wb");

    if (!src || !dest) {
        printf("Failed to open source or destination file.\n");
        if (src) fclose(src);
        if (dest) fclose(dest);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File downloaded to: %s\n", dest_path);
    log_action(user, "Downloaded file (via search)", filename);
}


void delete_file() {
    const char *user = get_current_user();
    if (user == NULL) {
        printf("No user is logged in!\n");
        return;
    }

    int user_file_indexes[100];
    int user_file_count = 0;

    printf("Your files:\n");
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files_db[i].owner, user) == 0) {
            user_file_indexes[user_file_count] = i;
            printf("[%d] %s  (Last Modified: %s)\n",
                   user_file_count + 1,
                   files_db[i].filename,
                   files_db[i].last_modified);
            user_file_count++;
        }
    }

    if (user_file_count == 0) {
        printf("You have no files to delete.\n");
        return;
    }

    int choice;
    printf("Enter the number of the file to delete: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > user_file_count) {
        printf("Invalid selection.\n");
        return;
    }

    int index_to_delete = user_file_indexes[choice - 1];
    char *filename = files_db[index_to_delete].filename;

    // Confirm deletion
    char confirm;
    printf("Are you sure you want to delete '%s'? (y/n): ", filename);
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf("Deletion cancelled.\n");
        return;
    }

    // Attempt to delete the actual file from disk
    if (unlink(files_db[index_to_delete].filepath) != 0) {
        printf("Warning: Failed to delete file from disk: %s\n", files_db[index_to_delete].filepath);
    } else {
        printf("File deleted: %s\n", filename);
    }

    // Shift remaining records up
    for (int j = index_to_delete; j < file_count - 1; j++) {
        files_db[j] = files_db[j + 1];
    }
    file_count--;

    log_action(user, "Deleted file", filename);
}
