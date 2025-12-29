#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }
    
    // Alusta SHA-256 konteksti
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        return NULL;
    }
    
    const EVP_MD *md = EVP_sha256();
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int hash_len;
    
    // Laske hash
    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1 ||
        EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1 ||
        EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    EVP_MD_CTX_free(mdctx);
    
    // Muunna hash heksadesimaalimerkkijonoksi
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