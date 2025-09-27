#ifndef CRYPTO_H
#define CRYPTO_H

char *hash_password(const char *password);
int verify_password(const char *password, const char *hash);
char *encrypt_data(const char *data);
char *decrypt_data(const char *encrypted_data);

#endif