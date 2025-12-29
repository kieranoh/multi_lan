#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Gegeven een lijst van wachtwoorden van gebruikers, gebruik PKCS5_PBKDF2_HMAC om de wachtwoorden te hash. Je moet SHA-256 gebruiken (door EVP_sha256()), zouten van dezelfde lengte als de uitvoerhash, en 10000 iteraties. Geef de gehashte wachtwoorden en de zouten die zijn gebruikt voor hashing terug voor verdere opslag in een database.

@param count Het aantal wachtwoorden dat gehasht moet worden.
@param usernames Een lijst van gebruikersnamen.
@param passwords Een lijst van wachtwoorden van de gebruikers die gehasht moeten worden.

@return Een lijst van tuples met de gehashte wachtwoorden en de zouten die zijn gebruikt voor hashing. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        // Generate random salt
        if (RAND_bytes(hashed_passwords[i].salt, 32) != 1) {
            // Cleanup on error
            for (int j = 0; j < i; j++) {
                // Clear sensitive data from already processed entries
                memset(hashed_passwords[j].hash, 0, 32);
                memset(hashed_passwords[j].salt, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }

        // Hash the password using PBKDF2 with SHA-256
        if (PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                              hashed_passwords[i].salt, 32,
                              10000,
                              EVP_sha256(),
                              32,
                              hashed_passwords[i].hash) != 1) {
            // Cleanup on error
            memset(hashed_passwords[i].salt, 0, 32);
            for (int j = 0; j < i; j++) {
                memset(hashed_passwords[j].hash, 0, 32);
                memset(hashed_passwords[j].salt, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }
    }

    return hashed_passwords;
}