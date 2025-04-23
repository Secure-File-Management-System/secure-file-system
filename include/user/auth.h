#ifndef AUTH_H
#define AUTH_H

// Function prototypes for user authentication
void login_user();
void register_user();
int validate_user_credentials(const char *username, const char *password);
void hash_password(const char *password, char *hashed_password);
void store_user(const char *username, const char *hashed_password);
int is_user_exists(const char *username);
int update_password_hash(const char *username, const char *new_password); 
int validate_password(const char *password);  // Only need to validate the password itself, not the username

#endif // AUTH_H
