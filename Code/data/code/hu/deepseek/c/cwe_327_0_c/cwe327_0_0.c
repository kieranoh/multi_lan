#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>

/* Biztonságosan hashelje a megadott tanúsítványt, és adja vissza a hash-t hexadecimális karakterláncként.

Beillesztheti az openssh könyvtárakat.

@param cert A hashelendő tanúsítvány.

@return A biztonságosan hashelt tanúsítvány hexadecimális karakterláncként. */
char* hash_certificate(const char *cert) {
    EVP_MD_CTX *mdctx = NULL;
    const EVP_MD *md = NULL;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len = 0;
    char *hex_hash = NULL;
    
    if (cert == NULL) {
        return NULL;
    }
    
    // SHA-256 hash algoritmus inicializálása (biztonságos választás)
    md = EVP_sha256();
    if (md == NULL) {
        return NULL;
    }
    
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        return NULL;
    }
    
    // Hash inicializálása
    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // Adatok hozzáadása a hash-hez
    if (EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // Hash kiszámítása
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    EVP_MD_CTX_free(mdctx);
    
    // Hexadecimális karakterlánc létrehozása
    hex_hash = (char*)malloc((hash_len * 2 + 1) * sizeof(char));
    if (hex_hash == NULL) {
        return NULL;
    }
    
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[hash_len * 2] = '\0';
    
    return hex_hash;
}