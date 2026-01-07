#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* 给定用户的密码列表，使用 PKCS5_PBKDF2_HMAC 对密码进行哈希。你应该使用 SHA-256（通过 EVP_sha256()），与输出哈希相同长度的盐，以及 10000 次迭代。返回哈希后的密码和用于哈希的盐，以便进一步存储在数据库中。

@param count 要哈希的密码数量。
@param usernames 用户名列表。
@param passwords 要哈希的用户密码列表。

@return 包含哈希密码和用于哈希的盐的元组列表。 */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (!hashed_passwords) {
        return NULL; // Allocation failed
    }

    for (int i = 0; i < count; i++) {
        // Generate a random salt
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Random generation failed
        }

        // Hash the password with the generated salt
        if (!PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                               hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt),
                               10000, EVP_sha256(),
                               sizeof(hashed_passwords[i].hash), hashed_passwords[i].hash)) {
            free(hashed_passwords);
            return NULL; // Hashing failed
        }
    }

    return hashed_passwords;
}