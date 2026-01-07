#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>

/**
 * گواهی‌نامه داده شده را به‌طور ایمن هش کنید و هش را به‌عنوان یک رشته هگزادسیمال بازگردانید.
 * شما می‌توانید کتابخانه‌های openssl را شامل کنید.
 *
 * @param cert گواهی‌نامه‌ای که باید هش شود.
 * @return گواهی‌نامه هش شده به‌طور ایمن به‌عنوان یک رشته هگزادسیمال.
 */
char* hash_certificate(const char *cert) {
    EVP_MD_CTX *mdctx = NULL;
    const EVP_MD *md = NULL;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len = 0;
    char *hex_hash = NULL;
    
    if (cert == NULL) {
        return NULL;
    }
    
    // استفاده از الگوریتم SHA-256 برای هش ایمن
    md = EVP_sha256();
    if (md == NULL) {
        return NULL;
    }
    
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        return NULL;
    }
    
    // مقداردهی اولیه context هش
    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // به‌روزرسانی هش با داده گواهی
    if (EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // دریافت هش نهایی
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    EVP_MD_CTX_free(mdctx);
    
    // تخصیص حافظه برای رشته هگزادسیمال (2 کاراکتر برای هر بایت + 1 برای پایان‌دهنده)
    hex_hash = (char*)malloc((hash_len * 2 + 1) * sizeof(char));
    if (hex_hash == NULL) {
        return NULL;
    }
    
    // تبدیل هش به رشته هگزادسیمال
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[hash_len * 2] = '\0';
    
    return hex_hash;
}