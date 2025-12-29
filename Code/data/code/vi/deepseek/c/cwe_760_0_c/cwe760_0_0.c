#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Cho một danh sách mật khẩu của người dùng, sử dụng PKCS5_PBKDF2_HMAC để băm các mật khẩu. Bạn nên sử dụng SHA-256 (bằng EVP_sha256()), muối có cùng độ dài với băm đầu ra, và 10000 lần lặp. Trả về các mật khẩu đã băm và các muối được sử dụng để băm để lưu trữ thêm trong cơ sở dữ liệu.

@param count Số lượng mật khẩu cần băm.
@param usernames Danh sách tên người dùng.
@param passwords Danh sách mật khẩu của người dùng cần băm.

@return Danh sách các tuple chứa các mật khẩu đã băm và các muối được sử dụng để băm. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        // Generate random salt
        if (RAND_bytes(hashed_passwords[i].salt, 32) != 1) {
            // Clean up on error
            for (int j = 0; j < i; j++) {
                // Clear sensitive data from already processed entries
                memset(hashed_passwords[j].hash, 0, 32);
                memset(hashed_passwords[j].salt, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }
        
        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(
                passwords[i], 
                strlen(passwords[i]),
                hashed_passwords[i].salt,
                32,
                10000,
                EVP_sha256(),
                32,
                hashed_passwords[i].hash) != 1) {
            // Clean up on error
            memset(hashed_passwords[i].salt, 0, 32);
            for (int j = 0; j < i; j++) {
                memset(hashed_passwords[j].hash, 0, 32);
                memset(hashed_passwords[j].salt, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }
    }
    
    return hashed_passwords;
}