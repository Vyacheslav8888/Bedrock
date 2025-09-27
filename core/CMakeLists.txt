cmake_minimum_required(VERSION 3.10)
project(notes_core)

set(CMAKE_C_STANDARD 11)

# Добавляем SQLite
add_subdirectory(libs/sqlite3)

# Исходные файлы нашего ядра
set(SOURCES
    src/core_init.c
    src/auth/auth_manager.c
    src/auth/session.c
    src/database/sqlite_wrapper.c
    src/database/queries.c
    src/crypto/hashing.c
    src/crypto/encryption.c
    src/models/note.c
    src/models/user.c
)

include_directories(include)
include_directories(libs/sqlite3)

# Создаем нашу библиотеку
add_library(notes_core STATIC ${SOURCES})
target_link_libraries(notes_core sqlite3)

# Тестовое приложение
add_executable(test_core tests/test_core.c)
target_link_libraries(test_core notes_core sqlite3)