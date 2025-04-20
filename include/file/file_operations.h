#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

// Function to upload a file (encrypt and store it securely)
int uploadFile(const char *fileName);

// Function to download a file (decrypt and retrieve it securely)
int downloadFile(const char *encryptedFileName, const char *outputFileName);

// Function to list all files in the storage directory
void listFiles();

// Function to search for a file by name
void searchFile(const char *searchTerm);

// Function to delete a file securely
int deleteFile(const char *fileName);

#endif // FILE_OPERATIONS_H