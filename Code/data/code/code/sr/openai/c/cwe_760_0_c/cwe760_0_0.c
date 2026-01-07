#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Datajte listu lozinki korisnika, koristite PKCS5_PBKDF2_HMAC za heširanje lozinki. Trebalo bi da koristite SHA-256 (putem EVP_sha256()), soli iste dužine kao izlazni heš, i 10000 iteracija. Vratite heširane lozinke i soli korišćene za heširanje za dalju pohranu u bazi podataka.

@param count Broj lozinki koje treba heširati.
@param usernames Lista korisničkih imena.
@param passwords Lista lozinki korisnika koje treba heširati.

@return Lista tuplova koja sadrži heširane lozinke i soli korišćene za heširanje. */
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

        // Derive the key using PBKDF2
        if (PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]), hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt), 10000, EVP_sha256(), sizeof(hashed_passwords[i].hash), hashed_passwords[i].hash) == 0) {
            free(hashed_passwords);
            return NULL; // Handle PBKDF2 failure
        }
    }

    return hashed_passwords;
}