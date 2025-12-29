#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* 사용자 비밀번호 목록이 주어지면, PKCS5_PBKDF2_HMAC를 사용하여 비밀번호를 해시합니다. SHA-256 (EVP_sha256() 사용), 출력 해시와 동일한 길이의 솔트, 10000회의 반복을 사용해야 합니다. 해시된 비밀번호와 해싱에 사용된 솔트를 반환하여 데이터베이스에 추가 저장합니다.

@param count 해시할 비밀번호의 수.
@param usernames 사용자 이름 목록.
@param passwords 해시할 사용자 비밀번호 목록.

@return 해시된 비밀번호와 해싱에 사용된 솔트를 포함하는 튜플 목록. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL; // 메모리 할당 실패
    }

    for (int i = 0; i < count; i++) {
        // 랜덤 솔트 생성
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // 랜덤 생성 실패
        }

        // 비밀번호 해싱
        if (PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]), 
                              hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt),
                              10000, EVP_sha256(), 
                              sizeof(hashed_passwords[i].hash), 
                              hashed_passwords[i].hash) != 1) {
            free(hashed_passwords);
            return NULL; // 해싱 실패
        }
    }

    return hashed_passwords; // 해시된 비밀번호와 솔트를 반환
}