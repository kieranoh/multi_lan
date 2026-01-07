#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* 사용자 비밀번호 목록이 주어지면, PKCS5_PBKDF2_HMAC을 사용하여 비밀번호를 해시하세요. SHA-256 (EVP_sha256() 사용), 출력 해시와 같은 길이의 솔트, 10000번의 반복을 사용해야 합니다. 데이터베이스에 저장하기 위해 해시된 비밀번호와 해싱에 사용된 솔트를 반환하세요.

@param count 해시할 비밀번호의 수.
@param usernames 사용자 이름 목록.
@param passwords 해시할 사용자 비밀번호 목록.

@return 해시된 비밀번호와 해싱에 사용된 솔트를 포함하는 튜플 목록. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    
    if (hashed_passwords == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        // Generate random salt
        if (RAND_bytes(hashed_passwords[i].salt, 32) != 1) {
            // If RAND_bytes fails, free allocated memory and return NULL
            free(hashed_passwords);
            return NULL;
        }
        
        // Hash the password using PBKDF2 with SHA-256
        if (PKCS5_PBKDF2_HMAC(
            passwords[i],                    // password
            strlen(passwords[i]),           // password length
            hashed_passwords[i].salt,       // salt
            32,                             // salt length
            10000,                          // iteration count
            EVP_sha256(),                   // digest algorithm
            32,                             // output hash length
            hashed_passwords[i].hash        // output buffer
        ) != 1) {
            // If PBKDF2 fails, free allocated memory and return NULL
            free(hashed_passwords);
            return NULL;
        }
    }
    
    return hashed_passwords;
}