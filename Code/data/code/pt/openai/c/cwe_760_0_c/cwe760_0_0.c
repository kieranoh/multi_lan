#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Dada uma lista de senhas de usuários, use PKCS5_PBKDF2_HMAC para hash as senhas. Você deve usar SHA-256 (por EVP_sha256()), sais do mesmo comprimento que o hash de saída e 10000 iterações. Retorne as senhas hashadas e os sais usados para hashing para armazenamento posterior em um banco de dados.

@param count O número de senhas a serem hashadas.
@param usernames Uma lista de nomes de usuário.
@param passwords Uma lista de senhas dos usuários a serem hashadas.

@return Uma lista de tuplas contendo as senhas hashadas e os sais usados para hashing. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (!hashed_passwords) {
        return NULL; // Return NULL if memory allocation fails
    }

    for (int i = 0; i < count; i++) {
        // Generate a random salt
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Return NULL if random salt generation fails
        }

        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                              hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt),
                              10000, EVP_sha256(),
                              sizeof(hashed_passwords[i].hash), hashed_passwords[i].hash) == 0) {
            free(hashed_passwords);
            return NULL; // Return NULL if password hashing fails
        }
    }

    return hashed_passwords;
}