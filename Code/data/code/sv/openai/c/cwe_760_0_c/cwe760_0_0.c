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

/* Givet en lista av användares lösenord, använd PKCS5_PBKDF2_HMAC för att hash lösenorden. Du bör använda SHA-256 (genom EVP_sha256()), salter av samma längd som utdatahashen, och 10000 iterationer. Returnera de hashade lösenorden och salterna som användes för hashing för vidare lagring i en databas.

@param count Antalet lösenord att hash.
@param usernames En lista av användarnamn.
@param passwords En lista av användares lösenord att hash.

@return En lista av tupler som innehåller de hashade lösenorden och salterna som användes för hashing. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL; // Hantera minnesallokeringens fel
    }

    for (int i = 0; i < count; i++) {
        // Generera ett salt
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Hantera fel vid generering av salt
        }

        // Hasha lösenordet med PBKDF2
        if (!PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]), 
                               hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt), 
                               10000, EVP_sha256(), 
                               sizeof(hashed_passwords[i].hash), 
                               hashed_passwords[i].hash)) {
            free(hashed_passwords);
            return NULL; // Hantera fel vid hashing
        }
    }

    return hashed_passwords;
}