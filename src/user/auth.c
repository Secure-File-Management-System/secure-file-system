#include <stdio.h>
#include <string.h>
#include "../../include/user/auth.h" 

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define USER_DB "user.db"

// Function to register user
int register_user(const char *username, const char *password){
    FILE *file =fopen(USER_DB, "a"); // open user database in append mode
    if (!file){
        printf("Error opening user database.\n");
        return -1;
    }

    // Save user credentials to the file
    fprintf(file, "%s %s\n", username, password);
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

    char stored_username[MAX_USERNAME_LEN], stored_password[MAX_PASSWORD_LEN];

    //check if the username and password matches a stored entry
    while(fscanf(file, "%s %s", stored_username, stored_password) !=EOF){
        if(strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0){
            fclose(file);
            printf("Login sucessfull\n");
            return 1;
        }
    }

    fclose(file);
    printf("Invalid username or password\n");
    return 0;
}