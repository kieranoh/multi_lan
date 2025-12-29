#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }
    
    EVP_MD_CTX *mdctx = NULL;
    const EVP_MD *md = NULL;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int hash_len = 0;
    char *hex_hash = NULL;
    
    // Инициализация контекста хеширования
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        return NULL;
    }
    
    // Используем SHA-256 для надежного хеширования
    md = EVP_sha256();
    if (md == NULL) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // Инициализация, обновление и финализация хеша
    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1 ||
        EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1 ||
        EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    EVP_MD_CTX_free(mdctx);
    
    // Преобразование бинарного хеша в шестнадцатеричную строку
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