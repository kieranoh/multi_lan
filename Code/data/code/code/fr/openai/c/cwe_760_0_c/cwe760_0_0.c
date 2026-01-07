#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

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
        return NULL; // Échec de l'allocation mémoire
    }

    for (int i = 0; i < count; i++) {
        // Générer un sel aléatoire
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Échec de la génération du sel
        }

        // Hacher le mot de passe avec le sel
        if (!PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]), 
                               hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt), 
                               10000, EVP_sha256(), 
                               sizeof(hashed_passwords[i].hash), 
                               hashed_passwords[i].hash)) {
            free(hashed_passwords);
            return NULL; // Échec du hachage
        }
    }

    return hashed_passwords; // Retourner le tableau de mots de passe hachés
}