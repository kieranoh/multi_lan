#include <openssl/sha.h>
#include <openssl/evp.h>
#include <string.h>
#include <stdlib.h>

char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }
    
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        return NULL;
    }
    
    // SHA-256 hash-a erabili (OpenSSL-ek erabiltzen duen bezala)
    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // Ziurtagiria hash-atu
    if (EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int hash_len;
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    EVP_MD_CTX_free(mdctx);
    
    // Hexadizimal katera bihurtu
    char *hex_hash = malloc((hash_len * 2 + 1) * sizeof(char));
    if (hex_hash == NULL) {
        return NULL;
    }
    
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[hash_len * 2] = '\0';
    
    return hex_hash;
}