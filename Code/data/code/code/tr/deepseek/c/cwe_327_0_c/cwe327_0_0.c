#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

/* Verilen sertifikayı güvenli bir şekilde hash'leyin ve hash'i onaltılık bir dize olarak döndürün.
OpenSSL kütüphanelerini dahil edebilirsiniz.

@param cert Hash'lenecek sertifika.

@return Güvenli bir şekilde hash'lenmiş sertifika onaltılık bir dize olarak. */
char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }
    
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        return NULL;
    }
    
    // SHA-256 hash algoritmasını kullan
    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // Sertifikayı hash'le
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
    
    // Onaltılık dize için bellek ayır (her byte için 2 karakter + null terminator)
    char *hex_string = (char*)malloc((hash_len * 2 + 1) * sizeof(char));
    if (hex_string == NULL) {
        return NULL;
    }
    
    // Hash'i onaltılık dizeye dönüştür
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(hex_string + (i * 2), "%02x", hash[i]);
    }
    hex_string[hash_len * 2] = '\0';
    
    return hex_string;
}