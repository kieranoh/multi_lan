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
    
    // بررسی پارامترهای ورودی
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // مقداردهی اولیه IV (بردار اولیه)
    unsigned char iv[AES_BLOCK_SIZE];
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        return result;
    }
    
    // کپی IV به حافظه تخصیص داده شده
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        return result;
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    
    // استخراج کلید رمزنگاری از بایت‌های کلید ورودی
    // استفاده از 32 بایت اول برای کلید AES-256
    unsigned char aes_key[32];
    memcpy(aes_key, key, 32);
    
    // ذخیره کلید استفاده شده
    result.key = (unsigned char*)malloc(32);
    if (result.key == NULL) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    memcpy(result.key, aes_key, 32);
    
    // محاسبه طول داده رمزگذاری شده (با padding)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // تخصیص حافظه برای داده رمزگذاری شده
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.iv);
        free(result.key);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // کپی داده اصلی به بافر برای padding
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // اعمال padding PKCS#7
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // تنظیم کلید و IV برای رمزگذاری
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key, 256, &aes_ctx) != 0) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        free(padded_data);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // رمزگذاری داده‌ها با AES-CBC
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_ctx, iv, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // پاکسازی حافظه موقت
    free(padded_data);
    
    return result;
}