#ifndef CORE_API_H
#define CORE_API_H

#ifdef __cplusplus
extern "C"
{
#endif

    // Базовые типы данных
    typedef struct User User;
    typedef struct Note Note;

    // Инициализация/деинициализация ядра
    int core_init(const char *db_path);
    void core_cleanup();

    // Функции базы данных (ДОБАВИТЬ ЭТИ СТРОКИ)
    int db_init(const char *db_path);
    void db_close();
    int db_exec(const char *sql);

    // Авторизация
    int auth_register(const char *username, const char *password);
    int auth_login(const char *username, const char *password);
    int auth_logout();
    int auth_is_logged_in();

    // Работа с заметками
    long notes_create(const char *title, const char *content);
    Note *notes_get_by_id(long id);
    int notes_get_all(Note ***notes, int *count);
    int notes_update(long id, const char *title, const char *content);
    int notes_delete(long id);

    // Утилиты
    void free_note(Note *note);
    void free_notes_array(Note **notes, int count);

#ifdef __cplusplus
}
#endif

#endif