#ifndef LOGGING_H
#define LOGGING_H

// Logs an action to the audit log file
// username: The user performing the action
// action: The action the user performed (e.g., "uploaded", "logged in")
// target: The file or object the action was performed on (can be NULL for actions like login)
void log_action(const char *username, const char *action, const char *target);

// Displays the content of the audit log
void view_audit_logs();

#endif // LOGGING_H
