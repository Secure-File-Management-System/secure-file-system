#ifndef SESSION_H
#define SESSION_H

// Function prototypes for session management
void start_session(const char *username);
void end_session();
const char *get_current_user();


#endif // SESSION_H
