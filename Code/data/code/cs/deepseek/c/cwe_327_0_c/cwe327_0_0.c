#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }
    
    // Inicializace kontextu SHA-256
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        return NULL;
    }
    
    // Inicializace hashování s SHA-256
    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // Přidání certifikátu do hashování
    if (EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // Získání výsledného hashe
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int hash_len;
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    EVP_MD_CTX_free(mdctx);
    
    // Alokace paměti pro hexadecimální řetězec (2 znaky na byte + null terminator)
    char *hex_hash = (char*)malloc((hash_len * 2 + 1) * sizeof(char));
    if (hex_hash == NULL) {
        return NULL;
    }
    
    // Převod hashe na hexadecimální řetězec
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[hash_len * 2] = '\0';
    
    return hex_hash;
}