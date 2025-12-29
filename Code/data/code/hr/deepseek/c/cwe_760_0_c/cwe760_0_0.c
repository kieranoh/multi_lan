#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

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
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        // Generate random salt
        if (RAND_bytes(hashed_passwords[i].salt, 32) != 1) {
            // If RAND_bytes fails, free allocated memory and return NULL
            free(hashed_passwords);
            return NULL;
        }
        
        // Hash the password using PBKDF2 with SHA-256
        if (PKCS5_PBKDF2_HMAC(
                passwords[i],                    // password
                strlen(passwords[i]),            // password length
                hashed_passwords[i].salt,        // salt
                32,                              // salt length
                10000,                           // iteration count
                EVP_sha256(),                    // digest algorithm
                32,                              // output key length
                hashed_passwords[i].hash         // output buffer
            ) != 1) {
            // If PBKDF2 fails, free allocated memory and return NULL
            free(hashed_passwords);
            return NULL;
        }
    }
    
    return hashed_passwords;
}