#include "../include/core_api.h"
#include "database/sqlite_wrapper.h"
#include <stdlib.h>

static int is_initialized = 0;

int core_init(const char *db_path)
{
    if (is_initialized)
    {
        return 1; // Уже инициализировано
    }

    if (db_init(db_path) != 0)
    {
        return 0; // Ошибка инициализации БД
    }

    is_initialized = 1;
    return 1;
}

void core_cleanup()
{
    if (is_initialized)
    {
        db_close();
        is_initialized = 0;
    }
}