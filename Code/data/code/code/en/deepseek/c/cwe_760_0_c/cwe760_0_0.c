#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/**
Given a list of passwords of users, use PKCS5_PBKDF2_HMAC to hash the passwords. You should use SHA-256 (by EVP_sha256()), salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database.

@param count The number of passwords to hash.
@param usernames A list of usernames.
@param passwords A list of passwords of the users to hash.

@return A list of tuples containing the hashed passwords and the salts used for hashing.
*/
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        // Generate random salt
        if (RAND_bytes(hashed_passwords[i].salt, 32) != 1) {
            // If RAND_bytes fails, clean up and return NULL
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
            32,                              // output hash length
            hashed_passwords[i].hash         // output buffer
        );
        
        if (result != 1) {
            // If hashing fails, clean up and return NULL
            free(hashed_passwords);
            return NULL;
        }
    }
    
    return hashed_passwords;
}