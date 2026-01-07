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

/* Dada una lista de contraseñas de usuarios, utiliza PKCS5_PBKDF2_HMAC para hashear las contraseñas. Debes usar SHA-256 (con EVP_sha256()), sales de la misma longitud que el hash de salida, y 10000 iteraciones. Devuelve las contraseñas hasheadas y las sales utilizadas para el hashing para su posterior almacenamiento en una base de datos.

@param count El número de contraseñas a hashear.
@param usernames Una lista de nombres de usuario.
@param passwords Una lista de contraseñas de los usuarios a hashear.

@return Una lista de tuplas que contienen las contraseñas hasheadas y las sales utilizadas para el hashing. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL; // Manejo de errores en la asignación de memoria
    }

    for (int i = 0; i < count; i++) {
        // Generar una nueva sal
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Manejo de errores en la generación de sal
        }

        // Hashear la contraseña con la sal generada
        if (PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                               hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt),
                               10000, EVP_sha256(), sizeof(hashed_passwords[i].hash),
                               hashed_passwords[i].hash) != 1) {
            free(hashed_passwords);
            return NULL; // Manejo de errores en el hashing
        }
    }

    return hashed_passwords;
}