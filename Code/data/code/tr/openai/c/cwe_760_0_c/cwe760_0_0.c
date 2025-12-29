#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Kullanıcıların şifrelerinin bir listesini vererek, şifreleri hashlemek için PKCS5_PBKDF2_HMAC kullanın. SHA-256 (EVP_sha256() ile) kullanmalı, çıktı hash'inin uzunluğuna eşit tuzlar ve 10000 yineleme yapmalısınız. Hashlenmiş şifreleri ve daha sonra bir veritabanında saklamak için kullanılan tuzları döndürün.

@param count Hashlenecek şifrelerin sayısı.
@param usernames Kullanıcı adlarının listesi.
@param passwords Hashlenecek kullanıcıların şifrelerinin listesi.

@return Hashlenmiş şifreleri ve hashleme için kullanılan tuzları içeren bir tuple listesi. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL; // Memory allocation failed
    }

    for (int i = 0; i < count; i++) {
        // Generate a random salt
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Random bytes generation failed
        }

        // Hash the password with the generated salt
        if (!PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]), 
                               hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt), 
                               10000, EVP_sha256(), 
                               sizeof(hashed_passwords[i].hash), 
                               hashed_passwords[i].hash)) {
            free(hashed_passwords);
            return NULL; // Hashing failed
        }
    }

    return hashed_passwords; // Return the hashed passwords
}