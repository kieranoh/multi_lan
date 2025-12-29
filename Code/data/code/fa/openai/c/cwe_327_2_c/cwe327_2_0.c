#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// ساختار برای نگهداری مقادیر بازگشتی
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* داده‌ها را با کلید با استفاده از حالت CBC رمزگذاری کنید.
بایت‌های کلید ارائه شده به اندازه کافی طولانی هستند (>= 64 بایت) برای تمام الگوریتم‌های موجود. فقط یک الگوریتم را برای پیاده‌سازی انتخاب کنید و پیشوند بایت‌های کلید ارائه شده را که با طول مورد نیاز مطابقت دارد، استفاده کنید. الگوریتم را بر اساس طول کلید انتخاب نکنید.
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
    size_t block_size = AES_BLOCK_SIZE;
    size_t padded_len = ((data_len + block_size) / block_size) * block_size;

    // تخصیص حافظه برای داده‌های رمزگذاری شده و IV
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    result.iv = (unsigned char*)malloc(block_size);
    result.key = (unsigned char*)malloc(key_len);

    // تولید IV تصادفی
    if (!RAND_bytes(result.iv, block_size)) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        result.encrypted_len = 0;
        return result;
    }

    // کپی کردن کلید به ساختار نتیجه
    memcpy(result.key, key, key_len);

    // تنظیم کلید AES
    if (AES_set_encrypt_key(result.key, key_len * 8, &aes_key) < 0) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        result.encrypted_len = 0;
        return result;
    }

    // رمزگذاری داده‌ها
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);

    result.encrypted_len = padded_len;
    return result;
}