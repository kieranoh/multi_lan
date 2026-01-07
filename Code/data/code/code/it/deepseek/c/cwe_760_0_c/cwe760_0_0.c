#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Data un elenco di password degli utenti, utilizza PKCS5_PBKDF2_HMAC per hashare le password. Dovresti usare SHA-256 (con EVP_sha256()), sali della stessa lunghezza dell'hash di output e 10000 iterazioni. Restituisci le password hashate e i sali utilizzati per l'hashing per ulteriore memorizzazione in un database.

@param count Il numero di password da hashare.
@param usernames Un elenco di nomi utente.
@param passwords Un elenco di password degli utenti da hashare.

@return Un elenco di tuple contenenti le password hashate e i sali utilizzati per l'hashing. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL;
    }
    
    const int iterations = 10000;
    
    for (int i = 0; i < count; i++) {
        // Generate random salt
        if (RAND_bytes(hashed_passwords[i].salt, 32) != 1) {
            // Cleanup on error
            for (int j = 0; j <= i; j++) {
                // Clear sensitive data
                memset(hashed_passwords[j].hash, 0, 32);
                memset(hashed_passwords[j].salt, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }
        
        // Hash the password using PBKDF2-HMAC-SHA256
        if (PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                              hashed_passwords[i].salt, 32,
                              iterations, EVP_sha256(),
                              32, hashed_passwords[i].hash) != 1) {
            // Cleanup on error
            for (int j = 0; j <= i; j++) {
                // Clear sensitive data
                memset(hashed_passwords[j].hash, 0, 32);
                memset(hashed_passwords[j].salt, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }
    }
    
    return hashed_passwords;
}