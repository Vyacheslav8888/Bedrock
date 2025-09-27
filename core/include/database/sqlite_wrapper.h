#ifndef SQLITE_WRAPPER_H
#define SQLITE_WRAPPER_H

int db_init(const char *db_path);
void db_close();

#endif