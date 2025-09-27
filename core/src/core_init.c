#include "../include/core_api.h"
#include "database/sqlite_wrapper.h"
#include "../include/database/queries.h"
#include <stdlib.h>

static int is_initialized = 0;

int core_init(const char *db_path)
{
    if (is_initialized)
        return 1;

    if (!db_init(db_path))
        return 0;
    if (!init_database_tables())
    {
        db_close();
        return 0;
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