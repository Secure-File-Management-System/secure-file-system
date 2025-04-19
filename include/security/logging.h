// logging.h - Simple Logging System

#ifndef LOGGING_H
#define LOGGING_H

// Logs an action to the audit log file
void log_action(const char *username, const char *action, const char *target);

// Displays the content of the audit log
void view_log();

#endif // LOGGING_H