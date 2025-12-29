#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Dając listę haseł użytkowników, użyj PKCS5_PBKDF2_HMAC do zhashowania haseł. Powinieneś użyć SHA-256 (przez EVP_sha256()), soli o tej samej długości co wynikowy hash oraz 10000 iteracji. Zwróć zhashowane hasła i sole użyte do haszowania do dalszego przechowywania w bazie danych.

@param count Liczba haseł do zhashowania.
@param usernames Lista nazw użytkowników.
@param passwords Lista haseł użytkowników do zhashowania.

@return Lista krotek zawierających zhashowane hasła i sole użyte do haszowania. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        // Generate random salt
        if (RAND_bytes(hashed_passwords[i].salt, 32) != 1) {
            // Cleanup on error
            for (int j = 0; j <= i; j++) {
                memset(hashed_passwords[j].hash, 0, 32);
                memset(hashed_passwords[j].salt, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }
        
        // Hash the password using PBKDF2 with SHA-256
        int result = PKCS5_PBKDF2_HMAC(
            passwords[i],                    // password
            strlen(passwords[i]),            // password length
            hashed_passwords[i].salt,        // salt
            32,                              // salt length
            10000,                           // iteration count
            EVP_sha256(),                    // digest algorithm
            32,                              // output length
            hashed_passwords[i].hash         // output buffer
        );
        
        if (result != 1) {
            // Cleanup on error
            for (int j = 0; j <= i; j++) {
                memset(hashed_passwords[j].hash, 0, 32);
                memset(hashed_passwords[j].salt, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }
    }
    
    return hashed_passwords;
}