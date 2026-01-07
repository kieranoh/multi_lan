#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // التحقق من المدخلات الأساسية
    if (!key || !data || key_len < 64) {
        return result;
    }
    
    // إنشاء IV (متجه التهيئة) - 16 بايت لـ AES-CBC
    unsigned char iv[AES_BLOCK_SIZE];
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        return result;
    }
    
    // نسخ IV إلى الذاكرة المخصصة
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!result.iv) {
        return result;
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    
    // استخدام أول 32 بايت من المفتاح المقدم كمفتاح AES-256
    const size_t aes_key_len = 32; // 256 بت
    result.key = (unsigned char*)malloc(aes_key_len);
    if (!result.key) {
        free(result.iv);
        return result;
    }
    memcpy(result.key, key, aes_key_len);
    
    // حساب حجم البيانات المشفرة (مضاعفات AES_BLOCK_SIZE)
    size_t padded_len = data_len;
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    if (padding != AES_BLOCK_SIZE) {
        padded_len += padding;
    }
    
    // تخصيص ذاكرة للبيانات المشفرة
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(result.iv);
        free(result.key);
        return result;
    }
    
    // نسخ البيانات الأصلية وإضافة التعبئة
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    // استخدام PKCS#7 padding
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = (unsigned char)padding;
    }
    
    // إعداد سياق AES للتشفير
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(padded_data);
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        return result;
    }
    
    // تشفير البيانات باستخدام AES-CBC
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);
    
    // تنظيف البيانات المعبأة
    free(padded_data);
    
    result.encrypted_len = padded_len;
    return result;
}