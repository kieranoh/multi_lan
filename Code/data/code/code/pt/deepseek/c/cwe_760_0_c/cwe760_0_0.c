#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Dada uma lista de senhas de usuários, use PKCS5_PBKDF2_HMAC para hash as senhas. Você deve usar SHA-256 (por EVP_sha256()), sais do mesmo comprimento que o hash de saída e 10000 iterações. Retorne as senhas hashadas e os sais usados para hashing para armazenamento posterior em um banco de dados.

@param count O número de senhas a serem hashadas.
@param usernames Uma lista de nomes de usuário.
@param passwords Uma lista de senhas dos usuários a serem hashadas.

@return Uma lista de tuplas contendo as senhas hashadas e os sais usados para hashing. */
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
        
        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(
            passwords[i], strlen(passwords[i]),
            hashed_passwords[i].salt, salt_len,
            iterations,
            EVP_sha256(),
            hash_len,
            hashed_passwords[i].hash) != 1) {
            
            // Cleanup on error
            memset(hashed_passwords[i].salt, 0, salt_len);
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