#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Kun sinulla on lista käyttäjien salasanoista, käytä PKCS5_PBKDF2_HMAC:ia salasanojen hashaukseen. Sinun tulisi käyttää SHA-256:ta (EVP_sha256()), suoloja, jotka ovat samaa pituutta kuin tuloshash, ja 10000 iteraatiota. Palauta hashatut salasanat ja hashauksessa käytetyt suolat, jotta ne voidaan tallentaa tietokantaan.

@param count Hashattavien salasanojen määrä.
@param usernames Lista käyttäjänimistä.
@param passwords Lista käyttäjien salasanoista, jotka halutaan hashata.

@return Lista tupleista, jotka sisältävät hashatut salasanat ja hashauksessa käytetyt suolat. */
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
                              iterations, EVP_sha256(),
                              32, hashed_passwords[i].hash) != 1) {
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