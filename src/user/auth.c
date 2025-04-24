#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include "../../include/menus/menus.h"
#include "../../include/user/auth.h"
#include "../../include/user/session.h"
#include "../../include/security/logging.h"

#define MAX_USERNAME_LEN 100
#define MAX_PASSWORD_LEN 100
#define USER_DB_FILE "user.db"
#define MAX_LINE 256
#define HASH_LEN 65 // 64 chars + null terminator for SHA-256

// Function to hash password using SHA-256
void hash_password(const char *password, char *hashed_password) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len = 0;

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, password, strlen(password));
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);
    EVP_MD_CTX_free(mdctx);

    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(&hashed_password[i * 2], "%02x", hash[i]);
    }

    hashed_password[hash_len * 2] = '\0';  // Null terminate the string
}

// Function to validate password strength (at least 8 characters)
int validate_password(const char *password) {
    if (strlen(password) < 8) {
        return 0;  // Invalid password
    }
    return 1;  // Valid password
}

// Function to register user
void register_user() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char hashed_password[HASH_LEN];

    printf("Enter a username: ");
    scanf("%s", username);

    if (is_user_exists(username)) {
        printf("Username already exists. Please try another.\n");
        register_user();  // Retry if the username exists
        return;
    }

    printf("Enter a password: ");
    scanf("%s", password);

    // Validate password strength
    if (!validate_password(password)) {
        printf("Password must be at least 8 characters long.\n");
        return;
    }

    // Hash the password before storing
    hash_password(password, hashed_password);
    store_user(username, hashed_password);

    printf("Registration successful!\n");
    log_action(username, "Registration successful", "system");  // Log successful registration
    login_user();  // Automatically log in after successful registration
}

// Function to check if a user exists
int is_user_exists(const char *username) {
    FILE *file = fopen(USER_DB_FILE, "r");
    if (!file) {
        return 0;  // File doesn't exist, so no users exist yet
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        char stored_username[MAX_USERNAME_LEN];
        char stored_password[HASH_LEN];
        sscanf(line, "%s %s", stored_username, stored_password);

        if (strcmp(stored_username, username) == 0) {
            fclose(file);
            return 1;  // User exists
        }
    }

    fclose(file);
    return 0;  // User does not exist
}

// Function to store user in the database file
void store_user(const char *username, const char *hashed_password) {
    FILE *file = fopen(USER_DB_FILE, "a");  // Open file for appending new users
    if (!file) {
        printf("Error: Unable to open user database file.\n");
        return;
    }

    // Append the new user details to the file
    fprintf(file, "%s %s\n", username, hashed_password);

    fclose(file);
}

// Function to validate user credentials
int validate_user_credentials(const char *username, const char *password) {
    FILE *file = fopen(USER_DB_FILE, "r");
    if (!file) {
        return 0;  // No users are registered yet
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        char stored_username[MAX_USERNAME_LEN];
        char stored_password[HASH_LEN];
        sscanf(line, "%s %s", stored_username, stored_password);

        if (strcmp(stored_username, username) == 0 && strcmp(stored_password, password) == 0) {
            fclose(file);
            return 1;  // Valid credentials
        }
    }

    fclose(file);
    return 0;  // Invalid credentials
}

// Function to login user
void login_user() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char hashed_password[HASH_LEN];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    // Hash the entered password
    hash_password(password, hashed_password);

    // Validate credentials
    if (validate_user_credentials(username, hashed_password)) {
        printf("Login successful!\n");
        start_session(username);  // Session management after login
        log_action(username, "Login successful", "system");  // Log the successful login
        show_main_menu(username);  // Show the main menu after login
    } else {
        printf("Invalid username or password. Try again.\n");
        log_action(username, "Login failed", "system"); // Log the failed login attempt
        login_user();  // Retry login
    }
}

// Function to update password hash in the user database
int update_password_hash(const char *username, const char *new_password) {
    FILE *file = fopen(USER_DB_FILE, "r+");  // Open file for reading and writing
    if (!file) {
        printf("Error: Unable to open user database file.\n");
        return 0;
    }

    char line[256];
    char stored_username[MAX_USERNAME_LEN];
    char stored_password[HASH_LEN];
    int user_found = 0;
    long pos;
    
    // Read the file line by line and find the user's password entry
    while (fgets(line, sizeof(line), file)) {
        pos = ftell(file);
        sscanf(line, "%s %s", stored_username, stored_password);

        // If the user is found, update their password
        if (strcmp(stored_username, username) == 0) {
            char new_hashed_password[HASH_LEN];
            hash_password(new_password, new_hashed_password);

            // Move to the start of the current user's entry
            fseek(file, pos - strlen(line), SEEK_SET);

            // Rewrite the user's password line with the new hash
            fprintf(file, "%s %s\n", stored_username, new_hashed_password);

            fflush(file);  // Flush changes to the file
            fclose(file);

            printf("Password updated successfully for user: %s\n", username);
            return 1;  // Password update success
        }
    }

    fclose(file);
    printf("User not found: %s\n", username);
    return 0;  // User not found
}

int update_user_password(const char *username, const char *new_password) {
    FILE *file = fopen(USER_DB_FILE, "r+");
    if (!file) {
        printf("Error: Unable to open user database file.\n");
        return 0;
    }

    char line[MAX_LINE];
    long pos;
    char stored_username[MAX_USERNAME_LEN];
    char stored_password[HASH_LEN];
    int user_found = 0;

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        pos = ftell(file);
        sscanf(line, "%s %s", stored_username, stored_password);

        if (strcmp(stored_username, username) == 0) {
            // Hash the new password
            char new_hashed_password[HASH_LEN];
            hash_password(new_password, new_hashed_password);

            // Go back to the position of the user's entry
            fseek(file, pos - strlen(line), SEEK_SET);

            // Rewrite the user's password
            fprintf(file, "%s %s\n", stored_username, new_hashed_password);

            fflush(file);  // Make sure the changes are written
            fclose(file);

            printf("Password updated successfully for user: %s\n", username);
            return 1;  // Password successfully updated
        }
    }

    fclose(file);
    printf("User not found: %s\n", username);
    return 0;  // User not found
}

