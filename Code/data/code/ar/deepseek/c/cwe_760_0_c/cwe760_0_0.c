#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* بالنظر إلى قائمة من كلمات مرور المستخدمين، استخدم PKCS5_PBKDF2_HMAC لتشفير كلمات المرور. يجب عليك استخدام SHA-256 (عن طريق EVP_sha256())، وأملاح بنفس طول ناتج التشفير، و10000 تكرار. أعد كلمات المرور المشفرة والأملاح المستخدمة للتشفير للتخزين الإضافي في قاعدة بيانات.

@param count عدد كلمات المرور التي سيتم تشفيرها.
@param usernames قائمة بأسماء المستخدمين.
@param passwords قائمة بكلمات مرور المستخدمين التي سيتم تشفيرها.

@return قائمة من التوائم تحتوي على كلمات المرور المشفرة والأملاح المستخدمة للتشفير. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        // Generate random salt
        if (RAND_bytes(hashed_passwords[i].salt, 32) != 1) {
            // Cleanup on error
            for (int j = 0; j < i; j++) {
                // Clear sensitive data from already processed entries
                memset(hashed_passwords[j].hash, 0, 32);
                memset(hashed_passwords[j].salt, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }
        
        // Hash the password using PBKDF2 with SHA-256
        if (PKCS5_PBKDF2_HMAC(
            passwords[i],                    // password
            strlen(passwords[i]),            // password length
            hashed_passwords[i].salt,        // salt
            32,                              // salt length
            10000,                           // iteration count
            EVP_sha256(),                    // digest algorithm
            32,                              // output key length
            hashed_passwords[i].hash         // output buffer
        ) != 1) {
            // Cleanup on error
            for (int j = 0; j <= i; j++) {
                memset(hashed_passwords[j].hash, 0, 32);
                memset(hashed_passwords[j].salt, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }
    }
    
    return hashed_passwords;
}