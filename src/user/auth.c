#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "../../include/user/auth.h" 

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define HASH_SIZE 65 // 64 char for SHA-256 +1 for null terminator
#define USER_DB "user.db"


// Function to hash a password using SHA-256
void hash_password(const char *password, char *hashed_output){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)password, strlen(password), hash);

    for ( int i = 0; i < SHA224_DIGEST_LENGTH; i++){
        sprintf(hashed_output + (i * 2), "%02x", hash[i]);
    }
    hashed_output[HASH_SIZE - 1] ='\0'; // Null-terminate the string
}

// Function to register user
int register_user(const char *username, const char *password){
    FILE *file =fopen(USER_DB, "a"); // open user database in append mode
    if (!file){
        printf("Error opening user database.\n");
        return -1;
    }

    char hashed_password[HASH_SIZE];
    hash_password(password, hashed_password);

    // Save user credentials to the file
    fprintf(file, "%s %s\n", username, hashed_password);
    fclose(file);

    printf("User %s registered sucessfully!\n", username);
    return 0;
}

//Function to authenticate user (login)
int authenticate_user(const char *username, const char *password){
    FILE *file =fopen(USER_DB, "r"); // open user database in read mode
    if(!file){
        printf("Error opening user database.\n");
        return -1;
    }

    char stored_username[MAX_USERNAME_LEN], stored_password[HASH_SIZE];
    char hashed_input[HASH_SIZE];

    hash_password(password, hashed_input); // Hash the input password

    //check if the username and password matches a stored entry
    while(fscanf(file, "%s %s", stored_username, stored_password) !=EOF){
        if(strcmp(username, stored_username) == 0 && strcmp(hashed_input, stored_password) == 0){
            fclose(file);
            printf("Login sucessfull\n");
            return 1;
        }
    }

    fclose(file);
    printf("Invalid username or password\n");
    return 0;
}