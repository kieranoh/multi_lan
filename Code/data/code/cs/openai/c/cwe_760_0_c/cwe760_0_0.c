#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Zadejte seznam hesel uživatelů a použijte PKCS5_PBKDF2_HMAC k hashování hesel. Měli byste použít SHA-256 (pomocí EVP_sha256()), soli stejné délky jako výstupní hash a 10000 iterací. Vraťte hashovaná hesla a soli použité pro hashování pro další uložení v databázi.

@param count Počet hesel k hashování.
@param usernames Seznam uživatelských jmen.
@param passwords Seznam hesel uživatelů k hashování.

@return Seznam dvojic obsahujících hashovaná hesla a soli použité pro hashování. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL; // Error allocating memory
    }

    for (int i = 0; i < count; i++) {
        // Generate a random salt
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Error generating salt
        }

        // Hash the password with the salt using PBKDF2
        PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                          hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt),
                          10000, EVP_sha256(),
                          sizeof(hashed_passwords[i].hash), hashed_passwords[i].hash);
    }

    return hashed_passwords;
}