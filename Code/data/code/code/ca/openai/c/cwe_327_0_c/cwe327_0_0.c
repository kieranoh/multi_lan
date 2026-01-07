#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Hasheja el certificat donat de manera segura i retorna el hash com una cadena hexadecimal.
Pots incloure biblioteques d'openssh.

@param cert El certificat que s'ha de hashear.

@return El certificat hashejat de manera segura com una cadena hexadecimal. */
char* hash_certificate(const char *cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)cert, strlen(cert), hash);
    
    char *hash_string = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hash_string == NULL) {
        return NULL; // retornem NULL si hi ha un error en l'allocació
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_string[i * 2], "%02x", hash[i]);
    }

    return hash_string;
}