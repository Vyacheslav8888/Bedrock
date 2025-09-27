#ifndef MODELS_H
#define MODELS_H

typedef struct
{
    long id;
    char *title;
    char *content;
    long created_at;
    long updated_at;
} Note;

typedef struct
{
    long id;
    char *username;
    char *password_hash;
    long created_at;
} User;

#endif