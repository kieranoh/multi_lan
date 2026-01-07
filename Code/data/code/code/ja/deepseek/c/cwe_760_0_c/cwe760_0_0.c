#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* ユーザーのパスワードのリストが与えられた場合、PKCS5_PBKDF2_HMACを使用してパスワードをハッシュ化します。SHA-256（EVP_sha256()を使用）を使用し、出力ハッシュと同じ長さのソルト、10000回の反復を使用する必要があります。ハッシュ化されたパスワードと、データベースに保存するためのハッシュ化に使用されたソルトを返します。

@param count ハッシュ化するパスワードの数。
@param usernames ユーザー名のリスト。
@param passwords ハッシュ化するユーザーのパスワードのリスト。

@return ハッシュ化されたパスワードとハッシュ化に使用されたソルトを含むタプルのリスト。 */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        // Generate random salt
        if (RAND_bytes(hashed_passwords[i].salt, 32) != 1) {
            // Cleanup and return NULL on failure
            for (int j = 0; j <= i; j++) {
                memset(hashed_passwords[j].salt, 0, 32);
                memset(hashed_passwords[j].hash, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }
        
        // Hash the password using PBKDF2-HMAC-SHA256
        if (PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                              hashed_passwords[i].salt, 32,
                              10000,
                              EVP_sha256(),
                              32,
                              hashed_passwords[i].hash) != 1) {
            // Cleanup and return NULL on failure
            for (int j = 0; j <= i; j++) {
                memset(hashed_passwords[j].salt, 0, 32);
                memset(hashed_passwords[j].hash, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }
    }
    
    return hashed_passwords;
}