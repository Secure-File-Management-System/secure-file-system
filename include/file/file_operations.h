#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#define MAX_FILE_NAME_LEN 256
#define MAX_FILE_PATH_LEN 512

// File structure
typedef struct File {
    char filename[MAX_FILE_NAME_LEN];
    char owner[MAX_FILE_NAME_LEN];
    char filepath[MAX_FILE_PATH_LEN];
    char last_modified[MAX_FILE_NAME_LEN];
} File;

// External file database and counter
extern File files_db[100];
extern int file_count;

// Function prototypes for file operations
void upload_file();
void download_file();
void list_files();
void search_files(const char *search_term);
void delete_file();
void load_files_metadata();
void save_files_metadata();


#endif // FILE_OPERATIONS_H
