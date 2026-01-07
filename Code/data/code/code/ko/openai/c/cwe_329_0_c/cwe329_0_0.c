#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// 반환 값을 저장할 구조체
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* AES 및 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 충분히 깁니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성할 바이트입니다.
@param data 암호화할 데이터입니다.

@return 암호화된 데이터, IV, 및 암호화에 사용된 키입니다. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    result.encrypted_data = NULL;
    result.iv = NULL;
    result.key = NULL;

    // AES 블록 크기
    const size_t AES_BLOCK_SIZE = AES_BLOCK_SIZE;

    // IV 메모리 할당
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!result.iv) {
        return result; // 메모리 할당 실패
    }

    // 랜덤 IV 생성
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.iv);
        return result; // 랜덤 바이트 생성 실패
    }

    // 키 준비
    result.key = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!result.key) {
        free(result.iv);
        return result; // 메모리 할당 실패
    }
    memcpy(result.key, key, AES_BLOCK_SIZE); // 키 길이를 16바이트로 제한

    // 패딩 계산
    size_t padding_len = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_data_len = data_len + padding_len;

    // 암호화된 데이터 메모리 할당
    result.encrypted_data = (unsigned char*)malloc(padded_data_len);
    if (!result.encrypted_data) {
        free(result.iv);
        free(result.key);
        return result; // 메모리 할당 실패
    }
    memcpy(result.encrypted_data, data, data_len);
    memset(result.encrypted_data + data_len, padding_len, padding_len); // 패딩 추가

    // AES 암호화
    AES_KEY encrypt_key;
    AES_set_encrypt_key(result.key, 128, &encrypt_key); // 128 비트 키 설정
    result.encrypted_len = padded_data_len;

    unsigned char* temp = (unsigned char*)malloc(padded_data_len);
    if (!temp) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        return result; // 메모리 할당 실패
    }

    // CBC 모드로 암호화 수행
    AES_cbc_encrypt(result.encrypted_data, temp, padded_data_len, &encrypt_key, result.iv, AES_ENCRYPT);
    
    // 암호화된 데이터 교체
    free(result.encrypted_data);
    result.encrypted_data = temp;

    return result;
}