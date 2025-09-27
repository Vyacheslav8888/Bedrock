#include "../../include/database/sqlite_wrapper.h"
#include "../../libs/sqlite3/sqlite3.h"
#include <stdio.h>

static sqlite3 *db = NULL;

int db_init(const char *db_path)
{
    int result = sqlite3_open(db_path, &db);
    if (result != SQLITE_OK)
    {
        printf("Database opening error: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    return 1;
}

void db_close()
{
    if (db)
    {
        sqlite3_close(db);
        db = NULL;
    }
}

int db_exec(const char *sql)
{
    if (!db)
        return 0;

    char *error_msg = NULL;
    int result = sqlite3_exec(db, sql, NULL, NULL, &error_msg);

    if (result != SQLITE_OK)
    {
        printf("SQL error: %s\n", error_msg);
        sqlite3_free(error_msg);
        return 0;
    }

    return 1;
}

int db_exec_with_params(const char *sql, const char **params, int param_count)
{
    // Реализация позже
    return db_exec(sql);
}