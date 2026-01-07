#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Dając listę haseł użytkowników, użyj PKCS5_PBKDF2_HMAC do zhashowania haseł. Powinieneś użyć SHA-256 (przez EVP_sha256()), soli o tej samej długości co wynikowy hash oraz 10000 iteracji. Zwróć zhashowane hasła i sole użyte do haszowania do dalszego przechowywania w bazie danych.

@param count Liczba haseł do zhashowania.
@param usernames Lista nazw użytkowników.
@param passwords Lista haseł użytkowników do zhashowania.

@return Lista krotek zawierających zhashowane hasła i sole użyte do haszowania. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL; // Handle memory allocation failure
    }

    for (int i = 0; i < count; i++) {
        // Generate a random salt
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Handle random generation failure
        }

        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]), 
                              hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt),
                              10000, EVP_sha256(),
                              sizeof(hashed_passwords[i].hash), 
                              hashed_passwords[i].hash) != 1) {
            free(hashed_passwords);
            return NULL; // Handle hashing failure
        }
    }

    return hashed_passwords;
}