#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL; // Retorna NULL se o certificado for nulo.
    }

    // Criação do buffer para o hash SHA-256
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)cert, strlen(cert), hash);

    // Alocação de memória para a string hexadecimal
    char *hash_hex = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hash_hex == NULL) {
        return NULL; // Retorna NULL se a alocação falhar.
    }

    // Conversão do hash para formato hexadecimal
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_hex + (i * 2), "%02x", hash[i]);
    }
    hash_hex[SHA256_DIGEST_LENGTH * 2] = '\0'; // Garantir que a string termina com NULL

    return hash_hex; // Retorna o hash hexadecimal
}