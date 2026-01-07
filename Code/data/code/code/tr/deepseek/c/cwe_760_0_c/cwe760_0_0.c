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
        return NULL;
    }
    
    const int iterations = 10000;
    const int hash_len = 32;
    const int salt_len = 32;
    
    for (int i = 0; i < count; i++) {
        // Generate random salt
        if (RAND_bytes(hashed_passwords[i].salt, salt_len) != 1) {
            // Cleanup on error
            for (int j = 0; j < i; j++) {
                // Clear sensitive data from already processed entries
                memset(hashed_passwords[j].hash, 0, hash_len);
                memset(hashed_passwords[j].salt, 0, salt_len);
            }
            free(hashed_passwords);
            return NULL;
        }
        
        // Hash the password using PBKDF2 with SHA-256
        int result = PKCS5_PBKDF2_HMAC(
            passwords[i],                    // password
            strlen(passwords[i]),            // password length
            hashed_passwords[i].salt,        // salt
            salt_len,                        // salt length
            iterations,                      // iteration count
            EVP_sha256(),                    // digest algorithm
            hash_len,                        // output length
            hashed_passwords[i].hash         // output buffer
        );
        
        if (result != 1) {
            // Clear sensitive data on error
            memset(hashed_passwords[i].salt, 0, salt_len);
            
            // Clear already processed entries
            for (int j = 0; j < i; j++) {
                memset(hashed_passwords[j].hash, 0, hash_len);
                memset(hashed_passwords[j].salt, 0, salt_len);
            }
            
            free(hashed_passwords);
            return NULL;
        }
    }
    
    return hashed_passwords;
}