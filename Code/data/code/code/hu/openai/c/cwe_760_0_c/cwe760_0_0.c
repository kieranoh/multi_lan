#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Felhasználók jelszavainak listáját megadva, használj PKCS5_PBKDF2_HMAC-ot a jelszavak hashelésére. SHA-256-ot kell használnod (az EVP_sha256() segítségével), az output hash-hez hasonló hosszúságú sókat, és 10000 iterációt. Térj vissza a hashelt jelszavakkal és a hasheléshez használt sókkal, hogy azokat további tárolásra egy adatbázisban felhasználhasd.

@param count A hashelendő jelszavak száma.
@param usernames A felhasználónevek listája.
@param passwords A hashelendő felhasználók jelszavainak listája.

@return A hashelt jelszavakat és a hasheléshez használt sókat tartalmazó tuple-ök listája. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (!hashed_passwords) {
        return NULL; // Memory allocation failed
    }

    for (int i = 0; i < count; i++) {
        // Generate a random salt
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Random byte generation failed
        }

        // Derive the key using PBKDF2 with HMAC-SHA256
        PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]), hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt), 
                          10000, EVP_sha256(), sizeof(hashed_passwords[i].hash), hashed_passwords[i].hash);
    }

    return hashed_passwords;
}