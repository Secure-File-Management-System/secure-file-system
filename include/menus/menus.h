#ifndef MENUS_H
#define MENUS_H

// Function prototypes for menu functions
void show_welcome_page();
void show_main_menu(const char *username);
void show_file_management_menu();
void show_search_results(const char *query, const char *results);
void show_security_settings_menu();
void view_audit_logs();

#endif // MENUS_H
