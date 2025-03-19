#include <stdio.h>
#include <string.h>
#include "auth.h"

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

//Function to at