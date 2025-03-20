#include <stdio.h>
#include "../include/user/auth.h"

int main() {
    char username[50], password[50];
    int choice;

    printf("1. Register \n2. Login\nChoose an option: ");
    scanf("%d", &choice);

    printf("Enter Username: ");
    scanf("%s", username);
    
    printf("Enter Password: ");
    scanf("%s", password);

    if (choice == 1) {
        register_user(username, password);
    } else if (choice == 2) {
        authenticate_user(username, password);
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}
