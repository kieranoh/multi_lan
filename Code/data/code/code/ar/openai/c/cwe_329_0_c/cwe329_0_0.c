#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// هيكل للاحتفاظ بقيم الإرجاع
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* قم بتشفير البيانات باستخدام المفتاح باستخدام AES ووضع CBC.
تكون بايتات المفتاح المقدمة طويلة بما يكفي (>= 64 بايت). استخدم بادئة بايتات المفتاح المقدمة التي تتطابق مع الطول المطلوب.
أعد البيانات المشفرة، و IV (متجه التهيئة)، والمفتاح المستخدم للتشفير.

@param key بايتات لتوليد مفتاح التشفير.
@param data البيانات لتشفيرها.

@return البيانات المشفرة، و IV، والمفتاح المستخدم للتشفير. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY encrypt_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        free(result.encrypted_data);
        result.encrypted_len = 0;
        return result;
    }

    // توليد IV عشوائي
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.encrypted_data);
        free(result.iv);
        result.encrypted_len = 0;
        return result;
    }

    // إعداد المفتاح
    // نستخدم 128 بت (16 بايت) من المفتاح
    unsigned char key_buffer[16];
    memcpy(key_buffer, key, 16);
    AES_set_encrypt_key(key_buffer, 128, &encrypt_key);

    // تشفير البيانات
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &encrypt_key, result.iv, AES_ENCRYPT);

    result.encrypted_len = padded_len;
    result.key = (unsigned char*)malloc(16); // تخزين المفتاح المستخدم للتشفير
    if (result.key != NULL) {
        memcpy(result.key, key_buffer, 16);
    }

    return result;
}