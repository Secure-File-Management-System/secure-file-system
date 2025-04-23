#ifndef AUTH_H
#define AUTH_H

// Function prototypes for user authentication
<<<<<<< HEAD
void login_user();  // Function for user login
void register_user();  // Function for user registration
int validate_user_credentials(const char *username, const char *password);  // Validates user credentials
void hash_password(const char *password, char *hashed_password);  // Hashes the user's password
void store_user(const char *username, const char *hashed_password);  // Stores the new user's credentials
int is_user_exists(const char *username);  // Checks if the user exists in the database
int update_password_hash(const char *username, const char *new_password);  // Updates password hash in DB
int validate_password(const char *password);  // Validates the password (e.g., length, complexity)
int update_user_password(const char *username, const char *new_password);  // Updates the user's password
int validate_current_password(const char *username, const char *current_password);
=======
void login_user();
void register_user();
int validate_user_credentials(const char *username, const char *password);
void hash_password(const char *password, char *hashed_password);
void store_user(const char *username, const char *hashed_password);
int is_user_exists(const char *username);
int update_password_hash(const char *username, const char *new_password); 
int validate_password(const char *password);  // Only need to validate the password itself, not the username
>>>>>>> 3ad65e5 (updated system)

#endif // AUTH_H
