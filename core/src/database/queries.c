#include "../../include/database/sqlite_wrapper.h"
#include <stdio.h>

int init_database_tables()
{
    // Создаем таблицу пользователей
    const char *users_table =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password_hash TEXT NOT NULL,"
        "created_at INTEGER DEFAULT (strftime('%s','now'))"
        ");";

    // Создаем таблицу заметок
    const char *notes_table =
        "CREATE TABLE IF NOT EXISTS notes ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "user_id INTEGER NOT NULL,"
        "title TEXT NOT NULL,"
        "content TEXT,"
        "created_at INTEGER DEFAULT (strftime('%s','now')),"
        "updated_at INTEGER DEFAULT (strftime('%s','now')),"
        "FOREIGN KEY (user_id) REFERENCES users (id)"
        ");";

    if (!db_exec(users_table))
        return 0;
    if (!db_exec(notes_table))
        return 0;

    return 1;
}