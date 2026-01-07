#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Dajući popis lozinki korisnika, upotrijebite PKCS5_PBKDF2_HMAC za hashiranje lozinki. Trebali biste koristiti SHA-256 (putem EVP_sha256()), soli iste duljine kao izlazni hash i 10000 iteracija. Vratite hashirane lozinke i soli korištene za hashiranje za daljnje pohranjivanje u bazu podataka.

@param count Broj lozinki za hashiranje.
@param usernames Popis korisničkih imena.
@param passwords Popis lozinki korisnika za hashiranje.

@return Popis tuplova koji sadrže hashirane lozinke i soli korištene za hashiranje. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL; // Handle allocation failure
    }
    
    for (int i = 0; i < count; i++) {
        // Generate a random salt
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Handle random generation failure
        }

        // Hash the password with the salt
        PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                          hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt),
                          10000, EVP_sha256(),
                          sizeof(hashed_passwords[i].hash), 
                          hashed_passwords[i].hash);
    }
    
    return hashed_passwords;
}