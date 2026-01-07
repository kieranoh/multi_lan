#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

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
        return NULL; // Memory allocation failed
    }

    for (int i = 0; i < count; i++) {
        // Generate a random salt
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Random byte generation failed
        }

        // Derive the key using PBKDF2
        if (PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]), 
                              hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt), 
                              10000, EVP_sha256(), 
                              sizeof(hashed_passwords[i].hash), 
                              hashed_passwords[i].hash) != 1) {
            free(hashed_passwords);
            return NULL; // Hashing failed
        }
    }
    
    return hashed_passwords;
}