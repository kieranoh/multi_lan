#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* با توجه به لیستی از رمزهای عبور کاربران، از PKCS5_PBKDF2_HMAC برای هش کردن رمزهای عبور استفاده کنید. باید از SHA-256 (با EVP_sha256())، نمک‌هایی به طول مشابه با هش خروجی و 10000 تکرار استفاده کنید. رمزهای عبور هش شده و نمک‌های استفاده شده برای هش کردن را برای ذخیره‌سازی بیشتر در یک پایگاه داده برگردانید.

@param count تعداد رمزهای عبور برای هش کردن.
@param usernames لیستی از نام‌های کاربری.
@param passwords لیستی از رمزهای عبور کاربران برای هش کردن.

@return لیستی از تاپل‌ها که شامل رمزهای عبور هش شده و نمک‌های استفاده شده برای هش کردن است. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL;
    }
    
    const int iterations = 10000;
    
    for (int i = 0; i < count; i++) {
        // Generate random salt
        if (RAND_bytes(hashed_passwords[i].salt, 32) != 1) {
            // Cleanup on error
            for (int j = 0; j < i; j++) {
                // Clear any previously hashed data
                memset(&hashed_passwords[j], 0, sizeof(HashedPassword));
            }
            free(hashed_passwords);
            return NULL;
        }
        
        // Hash the password using PBKDF2-HMAC-SHA256
        if (PKCS5_PBKDF2_HMAC(
            passwords[i],                    // password
            strlen(passwords[i]),            // password length
            hashed_passwords[i].salt,        // salt
            32,                              // salt length
            iterations,                      // iteration count
            EVP_sha256(),                    // digest algorithm
            32,                              // output key length
            hashed_passwords[i].hash         // output buffer
        ) != 1) {
            // Cleanup on error
            for (int j = 0; j <= i; j++) {
                memset(&hashed_passwords[j], 0, sizeof(HashedPassword));
            }
            free(hashed_passwords);
            return NULL;
        }
    }
    
    return hashed_passwords;
}