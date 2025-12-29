#include <openssl/aes.h>
#include <openssl/des.h>
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
    
    // انتخاب الگوریتم AES-256-CBC (ثابت شده، بدون توجه به طول کلید ورودی)
    const int algorithm_key_len = 32; // 32 بایت = 256 بیت برای AES-256
    const int iv_len = AES_BLOCK_SIZE; // 16 بایت برای AES
    
    // بررسی پارامترهای ورودی
    if (key == NULL || data == NULL || key_len < algorithm_key_len) {
        return result;
    }
    
    // تخصیص حافظه برای کلید استفاده شده
    result.key = (unsigned char*)malloc(algorithm_key_len);
    if (result.key == NULL) {
        return result;
    }
    
    // کپی کردن پیشوند کلید ورودی به اندازه مورد نیاز الگوریتم
    memcpy(result.key, key, algorithm_key_len);
    
    // تخصیص حافظه برای IV
    result.iv = (unsigned char*)malloc(iv_len);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // تولید IV تصادفی
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // محاسبه اندازه داده‌های رمزگذاری شده (با padding)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // تنظیم کلید و IV برای رمزگذاری
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, algorithm_key_len * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // رمزگذاری داده‌ها با AES-CBC
    // کپی داده‌ها به بافر خروجی برای رمزگذاری در محل
    memcpy(result.encrypted_data, data, data_len);
    
    // اضافه کردن padding به صورت دستی (PKCS#7)
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        result.encrypted_data[i] = pad_value;
    }
    
    // انجام رمزگذاری CBC
    unsigned char ivec[AES_BLOCK_SIZE];
    memcpy(ivec, result.iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(result.encrypted_data, result.encrypted_data, 
                    padded_len, &aes_key, ivec, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    return result;
}