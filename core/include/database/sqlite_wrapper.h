#ifndef SQLITE_WRAPPER_H
#define SQLITE_WRAPPER_H

int db_init(const char *db_path);
void db_close();
int db_exec(const char *sql);
int db_exec_with_params(const char *sql, const char **params, int param_count);

#endif