#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

// هيكل للاحتفاظ بقيم الإرجاع
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* قم بتشفير البيانات باستخدام المفتاح بطريقة CBC.
تكون بايتات المفتاح المقدمة طويلة بما يكفي (>= 64 بايت) لجميع الخوارزميات المتاحة. اختر خوارزمية واحدة فقط للتنفيذ واستخدم بادئة بايتات المفتاح المقدمة التي تتطابق مع الطول المطلوب. لا تختار الخوارزمية بناءً على طول المفتاح.
أعد البيانات المشفرة، و IV (متجه التهيئة)، والمفتاح المستخدم للتشفير.

@param key بايتات لتوليد مفتاح التشفير.
@param data البيانات لتشفيرها.

@return البيانات المشفرة، و IV، والمفتاح المستخدم للتشفير. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(AES_BLOCK_SIZE);
    
    // إعداد المفتاح
    memcpy(result.key, key, AES_BLOCK_SIZE);
    
    // إنشاء IV عشوائي
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    
    // إعداد AES
    AES_set_encrypt_key(result.key, 128, &aes_key);
    
    // التشفير
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    return result;
}