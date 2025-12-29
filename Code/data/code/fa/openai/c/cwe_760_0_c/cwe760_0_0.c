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
        return NULL; // Handle memory allocation failure
    }

    for (int i = 0; i < count; i++) {
        // Generate a random salt
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Handle random generation failure
        }

        // Hash the password using PBKDF2 with SHA-256
        if (PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                              hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt),
                              10000, EVP_sha256(),
                              sizeof(hashed_passwords[i].hash), 
                              hashed_passwords[i].hash) == 0) {
            free(hashed_passwords);
            return NULL; // Handle hashing failure
        }
    }

    return hashed_passwords;
}