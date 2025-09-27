# Bedrock - Notes App

Кроссплатформенное приложение заметок с C ядром.

## Структура проекта

- `core/` - C ядро (логика, БД, шифрование)
- `android/` - Android приложение (Kotlin)
- `web/` - Веб-версия (Vue.js + WebAssembly)
- `server/` - Бэкенд для синхронизации

## Сборка

```bash
cd core
mkdir build && cd build
cmake .. && make
```
