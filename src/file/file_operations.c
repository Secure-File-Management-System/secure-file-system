#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"
#include "encryption.h"  // Assuming you have encryption functions

int uploadFile(const char *fileName) {
    FILE *file = fopen(fileName, "rb"); // Open file in binary mode
    if (!file) {
        perror("Error opening file");
        return -1; // Return error if file couldn't be opened
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate buffer for file content
    char *fileBuffer = malloc(fileSize);
    if (!fileBuffer) {
        perror("Memory allocation failed");
        fclose(file);
        return -1;
    }

    // Read the file into the buffer
    fread(fileBuffer, 1, fileSize, file);
    fclose(file);

    // Encrypt file content (you'll need to implement the encryption logic)
    encrypt(fileBuffer, fileSize);  // Assume `encrypt` is your encryption function

    // Store encrypted file (you can modify the filename to store encrypted versions)
    char encryptedFileName[256];
    snprintf(encryptedFileName, sizeof(encryptedFileName), "%s.enc", fileName);

    file = fopen(encryptedFileName, "wb");  // Open new file for writing encrypted content
    if (!file) {
        perror("Error opening file for writing");
        free(fileBuffer);
        return -1;
    }

    // Write the encrypted content to the file
    fwrite(fileBuffer, 1, fileSize, file);
    fclose(file);

    free(fileBuffer); // Don't forget to free the buffer after usage

    printf("File uploaded and encrypted as %s\n", encryptedFileName);
    return 0; // Success
}
int downloadFile(const char *encryptedFileName, const char *outputFileName) {
    FILE *file = fopen(encryptedFileName, "rb"); // Open encrypted file
    if (!file) {
        perror("Error opening encrypted file");
        return -1;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate buffer for encrypted content
    char *fileBuffer = malloc(fileSize);
    if (!fileBuffer) {
        perror("Memory allocation failed");
        fclose(file);
        return -1;
    }

    // Read encrypted file into the buffer
    fread(fileBuffer, 1, fileSize, file);
    fclose(file);

    // Decrypt file content (you'll need to implement the decryption logic)
    decrypt(fileBuffer, fileSize);  // Assume `decrypt` is your decryption function

    // Open output file to save decrypted content
    file = fopen(outputFileName, "wb");  // Open new file for writing decrypted content
    if (!file) {
        perror("Error opening file for writing");
        free(fileBuffer);
        return -1;
    }

    // Write decrypted content to the output file
    fwrite(fileBuffer, 1, fileSize, file);
    fclose(file);

    free(fileBuffer); // Don't forget to free the buffer after usage

    printf("File downloaded and decrypted as %s\n", outputFileName);
    return 0; // Success
}
#include <dirent.h>
#include <stdio.h>

void listFiles() {
    struct dirent *entry;
    DIR *dp = opendir("."); // Open current directory

    if (dp == NULL) {
        perror("Error opening directory");
        return;
    }

    printf("List of files in current directory:\n");

    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_type == DT_REG) { // Only regular files
            printf("%s\n", entry->d_name); // Print file name
        }
    }

    closedir(dp); // Don't forget to close the directory when done
}