#ifndef AUTH_H
#define AUTH_H

// Function to register a new user
int register_user(const char *username, const char *password);

// Function to authenticate a user (login)
int authenticate_user(const char *username, const char *password);


#endif // AUTH_H