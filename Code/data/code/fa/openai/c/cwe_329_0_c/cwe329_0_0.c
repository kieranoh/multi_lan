#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// ساختاری برای نگهداری مقادیر بازگشتی
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* داده‌ها را با کلید با استفاده از AES و حالت CBC رمزگذاری کنید.
طول بایت‌های کلید ارائه شده کافی است (>= 64 بایت). از پیشوند بایت‌های کلید ارائه شده که با طول مورد نیاز مطابقت دارد استفاده کنید.
داده‌های رمزگذاری شده، IV (بردار اولیه) و کلید استفاده شده برای رمزگذاری را برگردانید.

@param key بایت‌ها برای تولید کلید رمزگذاری.
@param data داده‌ای که باید رمزگذاری شود.

@return داده‌های رمزگذاری شده، IV و کلید استفاده شده برای رمزگذاری. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padding_len;
    size_t encrypted_data_len;

    // ایجاد IV تصادفی
    if (!RAND_bytes(iv, sizeof(iv))) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // محاسبه طول داده‌های رمزگذاری شده
    padding_len = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    encrypted_data_len = data_len + padding_len;

    // تخصیص حافظه برای داده‌های رمزگذاری شده
    result.encrypted_data = (unsigned char*)malloc(encrypted_data_len);
    if (result.encrypted_data == NULL) {
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // تخصیص حافظه برای کلید استفاده شده
    result.key = (unsigned char*)malloc(key_len);
    if (result.key == NULL) {
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }
    memcpy(result.key, key, key_len);

    // تنظیم کلید AES
    AES_set_encrypt_key(result.key, key_len * 8, &aes_key);

    // اضافه کردن پدینگ به داده‌ها
    unsigned char* padded_data = (unsigned char*)malloc(encrypted_data_len);
    if (padded_data == NULL) {
        free(result.encrypted_data);
        free(result.key);
        result.encrypted_data = NULL;
        return result;
    }
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, padding_len, padding_len);

    // رمزگذاری داده‌ها
    AES_cbc_encrypt(padded_data, result.encrypted_data, encrypted_data_len, &aes_key, iv, AES_ENCRYPT);
    
    // آزادسازی حافظه موقتی
    free(padded_data);

    // تنظیم مقادیر بازگشتی
    result.encrypted_len = encrypted_data_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    memcpy(result.iv, iv, AES_BLOCK_SIZE);

    return result;
}