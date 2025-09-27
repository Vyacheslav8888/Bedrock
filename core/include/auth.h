#ifndef AUTH_H
#define AUTH_H

int auth_register(const char *username, const char *password);
int auth_login(const char *username, const char *password);
int auth_logout();
int auth_is_logged_in();

#endif