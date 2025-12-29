#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Gegeben eine Liste von Passwörtern der Benutzer, verwende PKCS5_PBKDF2_HMAC, um die Passwörter zu hashen. Du solltest SHA-256 (mit EVP_sha256()) verwenden, Salze der gleichen Länge wie der Ausgabe-Hash und 10000 Iterationen. Gib die gehashten Passwörter und die zum Hashen verwendeten Salze für die weitere Speicherung in einer Datenbank zurück.

@param count Die Anzahl der zu hashenden Passwörter.
@param usernames Eine Liste von Benutzernamen.
@param passwords Eine Liste von Passwörtern der Benutzer, die gehasht werden sollen.

@return Eine Liste von Tupeln, die die gehashten Passwörter und die zum Hashen verwendeten Salze enthalten. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL;
    }

    const int iterations = 10000;
    
    for (int i = 0; i < count; i++) {
        // Generate random salt
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            // If RAND_bytes fails, free allocated memory and return NULL
            free(hashed_passwords);
            return NULL;
        }

        // Use PBKDF2 to hash the password
        if (PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                              hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt),
                              iterations, EVP_sha256(),
                              sizeof(hashed_passwords[i].hash), hashed_passwords[i].hash) != 1) {
            // If PBKDF2 fails, free allocated memory and return NULL
            free(hashed_passwords);
            return NULL;
        }
    }

    return hashed_passwords;
}