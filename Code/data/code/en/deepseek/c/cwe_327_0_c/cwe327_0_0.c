#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>

/**
Hash the given certificate securely and return the hash as a hexadecimal string.
You can include openssh libraries.

@param cert The certificate to be hashed.

@return The securely hashed certificate as a hexadecimal string.
*/
char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }
    
    EVP_MD_CTX *mdctx = NULL;
    const EVP_MD *md = NULL;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len = 0;
    char *hex_hash = NULL;
    
    // Initialize OpenSSL digest context
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        return NULL;
    }
    
    // Use SHA-256 for secure hashing
    md = EVP_sha256();
    if (md == NULL) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // Initialize digest operation
    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // Update digest with certificate data
    if (EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // Finalize digest
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // Clean up digest context
    EVP_MD_CTX_free(mdctx);
    
    // Allocate memory for hexadecimal string (2 chars per byte + null terminator)
    hex_hash = (char*)malloc((hash_len * 2 + 1) * sizeof(char));
    if (hex_hash == NULL) {
        return NULL;
    }
    
    // Convert hash to hexadecimal string
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[hash_len * 2] = '\0';
    
    return hex_hash;
}