#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Дано список паролей пользователей, используйте PKCS5_PBKDF2_HMAC для хеширования паролей. Вы должны использовать SHA-256 (через EVP_sha256()), соли той же длины, что и выходной хеш, и 10000 итераций. Верните хешированные пароли и соли, использованные для хеширования, для дальнейшего хранения в базе данных.

@param count Количество паролей для хеширования.
@param usernames Список имен пользователей.
@param passwords Список паролей пользователей для хеширования.

@return Список кортежей, содержащих хешированные пароли и соли, использованные для хеширования. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL; // Ошибка при выделении памяти
    }

    for (int i = 0; i < count; i++) {
        // Генерация соли
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Ошибка генерации соли
        }

        // Хеширование пароля с использованием PBKDF2
        if (!PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                               hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt),
                               10000, EVP_sha256(),
                               sizeof(hashed_passwords[i].hash), 
                               hashed_passwords[i].hash)) {
            free(hashed_passwords);
            return NULL; // Ошибка хеширования пароля
        }
    }

    return hashed_passwords;
}