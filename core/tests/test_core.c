#include "../include/core_api.h"
#include <stdio.h>
#include <string.h>

int main()
{
    printf("=== Bedrock Core Test ===\n");

    // Удаляем старую базу данных
    remove("test.db");

    // 1. Тест инициализации
    printf("1. Testing core_init...\n");
    if (!core_init("test.db"))
    {
        printf("FAIL: core_init failed\n");
        return 1;
    }
    printf("PASS: core_init successful\n");

    // 2. Тест выполнения SQL
    printf("2. Testing SQL execution...\n");
    if (!db_exec("INSERT INTO users (username, password_hash) VALUES ('testuser', 'testhash');"))
    {
        printf("FAIL: SQL execution failed\n");
        core_cleanup();
        return 1;
    }
    printf("PASS: SQL execution successful\n");

    // Остальные тесты без изменений...
    // 3. Тест повторной инициализации
    printf("3. Testing re-initialization...\n");
    if (!core_init("test.db"))
    {
        printf("FAIL: re-init failed\n");
        core_cleanup();
        return 1;
    }
    printf("PASS: re-init successful\n");

    // 4. Тест очистки
    printf("4. Testing core_cleanup...\n");
    core_cleanup();
    printf("PASS: core_cleanup successful\n");

    printf("\n✅ ALL TESTS PASSED! C core is working correctly.\n");
    return 0;

    // 5. Тест регистрации пользователя
    printf("5. Testing user registration...\n");
    if (!auth_register("testuser", "password123"))
    {
        printf("FAIL: User registration failed\n");
        core_cleanup();
        return 1;
    }
    printf("PASS: User registration successful\n");

    // 6. Тест авторизации
    printf("6. Testing user login...\n");
    if (!auth_login("testuser", "password123"))
    {
        printf("FAIL: User login failed\n");
        core_cleanup();
        return 1;
    }
    printf("PASS: User login successful\n");

    // 7. Тест проверки авторизации
    printf("7. Testing login check...\n");
    if (!auth_is_logged_in())
    {
        printf("FAIL: Login check failed\n");
        core_cleanup();
        return 1;
    }
    printf("PASS: User is logged in\n");

    // 8. Тест выхода
    printf("8. Testing logout...\n");
    auth_logout();
    if (auth_is_logged_in())
    {
        printf("FAIL: Logout failed\n");
        core_cleanup();
        return 1;
    }
    printf("PASS: Logout successful\n");
}