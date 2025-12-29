#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Donada una llista de contrasenyes d'usuaris, utilitzeu PKCS5_PBKDF2_HMAC per fer hash de les contrasenyes. Heu d'utilitzar SHA-256 (per EVP_sha256()), salts de la mateixa longitud que el hash de sortida, i 10000 iteracions. Retorneu les contrasenyes hashades i els salts utilitzats per al hashing per a un emmagatzematge posterior en una base de dades.

@param count El nombre de contrasenyes a fer hash.
@param usernames Una llista de noms d'usuari.
@param passwords Una llista de contrasenyes dels usuaris a fer hash.

@return Una llista de tuples que contenen les contrasenyes hashades i els salts utilitzats per al hashing. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL; // Error al malloc
    }

    for (int i = 0; i < count; i++) {
        // Generar un salt aleatori
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Error al generar el salt
        }

        // Fer hash de la contrasenya amb el salt utilitzant PBKDF2
        PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]), 
                          hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt), 
                          10000, EVP_sha256(), 
                          sizeof(hashed_passwords[i].hash), 
                          hashed_passwords[i].hash);
    }

    return hashed_passwords; // Retornar llista de contrasenyes hashades i salts
}