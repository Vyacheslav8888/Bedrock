#include "../../include/auth.h"
#include "../../include/database/sqlite_wrapper.h"
#include "../../include/crypto.h"
#include <string.h>
#include <stdio.h>

static int current_user_id = 0;

int auth_register(const char *username, const char *password)
{
    if (!username || !password)
        return 0;

    printf("Registering user: %s\n", username);
    return 1; // временная заглушка
}

int auth_login(const char *username, const char *password)
{
    if (!username || !password)
        return 0;

    printf("User logged in: %s\n", username);
    current_user_id = 1;
    return 1;
}

int auth_logout()
{
    current_user_id = 0;
    printf("User logged out\n");
    return 1;
}

int auth_is_logged_in()
{
    return current_user_id > 0;
}