#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

// 반환 값을 저장할 구조체
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 모든 사용 가능한 알고리즘에 대해 충분히 깁니다(>= 64 바이트). 구현할 알고리즘을 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 키의 길이에 따라 알고리즘을 선택하지 마세요.
암호화된 데이터, IV(초기화 벡터), 그리고 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성하기 위한 바이트.
@param data 암호화할 데이터.

@return 암호화된 데이터, IV, 그리고 암호화에 사용된 키. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // AES-256-CBC를 사용하기로 선택 (키 길이: 32바이트, IV 길이: 16바이트)
    const int AES_KEY_LENGTH = 32; // 256비트
    const int AES_IV_LENGTH = 16;  // 128비트
    
    // 키 길이 검증
    if (key_len < AES_KEY_LENGTH) {
        // 키가 너무 짧으면 실패
        return result;
    }
    
    // IV 생성
    unsigned char* iv = (unsigned char*)malloc(AES_IV_LENGTH);
    if (!iv) {
        return result;
    }
    
    if (RAND_bytes(iv, AES_IV_LENGTH) != 1) {
        free(iv);
        return result;
    }
    
    // 암호화 키 생성 (제공된 키의 처음 32바이트 사용)
    unsigned char* aes_key = (unsigned char*)malloc(AES_KEY_LENGTH);
    if (!aes_key) {
        free(iv);
        return result;
    }
    memcpy(aes_key, key, AES_KEY_LENGTH);
    
    // AES 컨텍스트 초기화
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key, 256, &aes_ctx) != 0) {
        free(iv);
        free(aes_key);
        return result;
    }
    
    // CBC 모드에서 암호화를 위한 패딩 계산
    // PKCS#7 패딩: 마지막 블록이 불완전한 경우, 부족한 바이트 수만큼 그 값을 채움
    size_t block_size = AES_BLOCK_SIZE;
    size_t padded_len = data_len + (block_size - (data_len % block_size));
    
    // 암호화된 데이터 버퍼 할당
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (!encrypted) {
        free(iv);
        free(aes_key);
        return result;
    }
    
    // 입력 데이터를 패딩하여 복사
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(iv);
        free(aes_key);
        free(encrypted);
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 패딩 적용
    unsigned char pad_value = block_size - (data_len % block_size);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // CBC 모드로 암호화
    unsigned char ivec[AES_IV_LENGTH];
    memcpy(ivec, iv, AES_IV_LENGTH);
    
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_ctx, ivec, AES_ENCRYPT);
    
    // 결과 구조체 채우기
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = aes_key;
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}