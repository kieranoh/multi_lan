#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>

char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }

    EVP_MD_CTX *mdctx = NULL;
    const EVP_MD *md = NULL;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len = 0;
    char *hex_hash = NULL;
    
    // SHA-256 का उपयोग करें क्योंकि यह सुरक्षित और मानक है
    md = EVP_sha256();
    if (md == NULL) {
        return NULL;
    }

    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        return NULL;
    }

    // हैशिंग प्रक्रिया शुरू करें
    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    // प्रमाणपत्र डेटा को हैश करें
    if (EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    // हैश प्राप्त करें
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    EVP_MD_CTX_free(mdctx);

    // हैश को हेक्साडेसिमल स्ट्रिंग में बदलें
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