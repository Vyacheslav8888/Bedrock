cmake_minimum_required(VERSION 3.10)
project(notes_core)

set(CMAKE_C_STANDARD 11)

# Добавляем SQLite
add_subdirectory(libs/sqlite3)


# Исходные файлы
set(SOURCES
    src/auth/auth_manager.c
    src/database/sqlite_wrapper.c
    src/database/queries.c
    src/crypto/hashing.c
    src/models/note.c
    src/core_init.c
)

# Заголовочные файлы
include_directories(include)
include_directories(libs/sqlite3)

# Создаем библиотеку
add_library(notes_core STATIC ${SOURCES})
target_link_libraries(notes_core sqlite3)

# Для Android добавим потом специальные настройки