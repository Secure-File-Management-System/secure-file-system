#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include "../../include/user/auth.h" 

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define HASH_SIZE 65 // 64 char for SHA-256 +1 for null terminator
#define USER_DB "user.db"

//Function to generate a random salt
void generate_salt(char *salt){
    RAND_bytes((unsigned char *)salt, SALT_SIZE);
    salt[SALT_SIZE -1 ] = '\0'; // ensure null termination
}


// Function to hash a password with salt using SHA-256
void hash_password(const char *password,  const char *salt, char *hashed_output){
    char combined[MAX_PASSWORD_LEN + SALT_SIZE];
    snprintf(combined, sizeof(combined), "%s%s" , salt, password);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)combined, strlen(combined), hash);

    for ( int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        sprintf(hashed_output + (i * 2), "%02x", hash[i]);
    }
    hashed_output[HASH_SIZE - 1] ='\0'; // Null-terminate the string
}

// Function to register user (store hashed password + salt)
int register_user(const char *username, const char *password){
    FILE *file =fopen(USER_DB, "a"); // open user database in append mode
    if (!file){
        printf("Error opening user database.\n");
        return -1;
    }
    
    char salt[SALT_SIZE];
    char hashed_password[HASH_SIZE];

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Save user credentials to the file
    fprintf(file, "%s %s %s\n", username, salt, hashed_password);
    fclose(file);

    printf("User %s registered sucessfully!\n", username);
    return 0;
}

//Function to authenticate user (login verify hashed password with salt)
int authenticate_user(const char *username, const char *password){
    FILE *file =fopen(USER_DB, "r"); // open user database in read mode
    if(!file){
        printf("Error opening user database.\n");
        return -1;
    }

    char stored_username[MAX_USERNAME_LEN], stored_salt[SALT_SIZE], stored_password[HASH_SIZE];
    char hashed_input[HASH_SIZE];

    

    //check if the username and password matches a stored entry
    while(fscanf(file, "%s %s %s", stored_salt, stored_password, stored_username) !=EOF){
        if(strcmp(username, stored_username) == 0 ) {
            hash_password(password, stored_salt, hashed_input); // Hash the input password plus salt
            if (strcmp(hashed_input, stored_password) == 0){
                fclose(file);
                printf("Login sucessfull\n");
                return 1;
            }
        } 
    }

    fclose(file);
    printf("Invalid username or password\n");
    return 0;
}