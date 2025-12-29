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
    
    // Khởi tạo OpenSSL (nếu chưa được khởi tạo)
    OpenSSL_add_all_digests();
    
    // Sử dụng SHA-256 để băm
    md = EVP_get_digestbyname("sha256");
    if (md == NULL) {
        fprintf(stderr, "SHA-256 digest not available\n");
        return NULL;
    }
    
    mdctx = EVP_MD_CTX_create();
    if (mdctx == NULL) {
        fprintf(stderr, "Failed to create message digest context\n");
        return NULL;
    }
    
    // Khởi tạo và cập nhật băm
    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1) {
        fprintf(stderr, "Failed to initialize digest\n");
        EVP_MD_CTX_destroy(mdctx);
        return NULL;
    }
    
    if (EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1) {
        fprintf(stderr, "Failed to update digest\n");
        EVP_MD_CTX_destroy(mdctx);
        return NULL;
    }
    
    // Lấy giá trị băm cuối cùng
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        fprintf(stderr, "Failed to finalize digest\n");
        EVP_MD_CTX_destroy(mdctx);
        return NULL;
    }
    
    // Chuyển đổi băm thành chuỗi hex
    hex_hash = (char*)malloc((hash_len * 2 + 1) * sizeof(char));
    if (hex_hash == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        EVP_MD_CTX_destroy(mdctx);
        return NULL;
    }
    
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[hash_len * 2] = '\0';
    
    // Dọn dẹp
    EVP_MD_CTX_destroy(mdctx);
    
    return hex_hash;
}