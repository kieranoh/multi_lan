#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }
    
    // إنشاء سياق SHA-256
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        return NULL;
    }
    
    // تهيئة خوارزمية التجزئة SHA-256
    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // تحديث التجزئة مع بيانات الشهادة
    if (EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // الحصول على التجزئة النهائية
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int hash_len;
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // تنظيف سياق التجزئة
    EVP_MD_CTX_free(mdctx);
    
    // تخصيص ذاكرة للسلسلة السداسية عشرية (2 حرف لكل بايت + 1 للنهاية)
    char *hex_hash = (char*)malloc((hash_len * 2 + 1) * sizeof(char));
    if (hex_hash == NULL) {
        return NULL;
    }
    
    // تحويل التجزئة إلى سلسلة سداسية عشرية
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[hash_len * 2] = '\0';
    
    return hex_hash;
}