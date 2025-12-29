#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

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
    
    // اختر خوارزمية واحدة فقط - سنستخدم AES-256-CBC
    const int algorithm = 1; // 1 لـ AES-256-CBC
    
    if (algorithm == 1) { // AES-256-CBC
        // AES-256-CBC يتطلب مفتاح 32 بايت و IV 16 بايت
        const int aes_key_len = 32;
        const int aes_iv_len = 16;
        
        // تخصيص ذاكرة للمفتاح و IV
        result.key = (unsigned char*)malloc(aes_key_len);
        result.iv = (unsigned char*)malloc(aes_iv_len);
        
        if (!result.key || !result.iv) {
            free(result.key);
            free(result.iv);
            return result;
        }
        
        // نسخ أول 32 بايت من المفتاح المقدم
        size_t copy_len = (key_len < aes_key_len) ? key_len : aes_key_len;
        memcpy(result.key, key, copy_len);
        
        // إذا كان المفتاح المقدم أقصر، املأ الباقي بالأصفار
        if (copy_len < aes_key_len) {
            memset(result.key + copy_len, 0, aes_key_len - copy_len);
        }
        
        // توليد IV عشوائي
        if (RAND_bytes(result.iv, aes_iv_len) != 1) {
            free(result.key);
            free(result.iv);
            return result;
        }
        
        // حساب حجم البيانات المشفرة (مضاعفات 16 بايت لـ AES-CBC)
        size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
        result.encrypted_data = (unsigned char*)malloc(padded_len);
        
        if (!result.encrypted_data) {
            free(result.key);
            free(result.iv);
            return result;
        }
        
        // إعداد سياق AES
        AES_KEY aes_key;
        if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
            free(result.encrypted_data);
            free(result.key);
            free(result.iv);
            return result;
        }
        
        // نسخ البيانات إلى المخزن المؤقت مع الحشو
        unsigned char* padded_data = (unsigned char*)malloc(padded_len);
        if (!padded_data) {
            free(result.encrypted_data);
            free(result.key);
            free(result.iv);
            return result;
        }
        
        memcpy(padded_data, data, data_len);
        
        // تطبيق حشو PKCS#7
        unsigned char pad_value = padded_len - data_len;
        for (size_t i = data_len; i < padded_len; i++) {
            padded_data[i] = pad_value;
        }
        
        // تنفيذ التشفير باستخدام CBC
        AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
        
        result.encrypted_len = padded_len;
        free(padded_data);
        
    } else if (algorithm == 2) { // DES-EDE3-CBC (ثلاثي DES)
        // هذا مجرد مثال للهيكل - الخوارزمية المختارة هي AES-256-CBC
        // لا يتم تنفيذ هذا الفرع في الكود الفعلي
    }
    
    return result;
}