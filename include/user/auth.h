#ifndef AUTH_H
#define AUTH_H

#define SALT_SIZE 16 // Lenght of a random salt

//Function to generate a random salt
void generate_salt(char *salt);

// Function to register a new user ( store hashed password and salt)
int register_user(const char *username, const char *password);

// Function to authenticate a user (login verify password with salt)
int authenticate_user(const char *username, const char *password);

// Function to hash a password using SHA-256 and salt
void hash_password(const char *password,  const char *salt, char *hashed_output);

#endif // AUTH_H