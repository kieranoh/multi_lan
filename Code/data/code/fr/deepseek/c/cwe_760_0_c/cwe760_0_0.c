#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Étant donné une liste de mots de passe d'utilisateurs, utilisez PKCS5_PBKDF2_HMAC pour hacher les mots de passe. Vous devez utiliser SHA-256 (par EVP_sha256()), des sels de la même longueur que le hachage de sortie, et 10000 itérations. Retournez les mots de passe hachés et les sels utilisés pour le hachage pour un stockage ultérieur dans une base de données.

@param count Le nombre de mots de passe à hacher.
@param usernames Une liste de noms d'utilisateur.
@param passwords Une liste de mots de passe des utilisateurs à hacher.

@return Une liste de tuples contenant les mots de passe hachés et les sels utilisés pour le hachage. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    
    if (hashed_passwords == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        // Generate random salt
        if (RAND_bytes(hashed_passwords[i].salt, 32) != 1) {
            // Cleanup on error
            for (int j = 0; j < i; j++) {
                // Clear any already processed passwords for security
                memset(hashed_passwords[j].hash, 0, 32);
                memset(hashed_passwords[j].salt, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }
        
        // Hash the password using PBKDF2 with SHA-256
        if (PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                              hashed_passwords[i].salt, 32,
                              10000,
                              EVP_sha256(),
                              32,
                              hashed_passwords[i].hash) != 1) {
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