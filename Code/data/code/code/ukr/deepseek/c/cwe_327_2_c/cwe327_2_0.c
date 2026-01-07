#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // 입력 유효성 검사
    if (key == NULL || data == NULL || key_len < 16 || data_len == 0) {
        return result;
    }
    
    // AES-256-CBC를 사용 (문서에 따라 하나의 알고리즘 선택)
    // AES-256 키 길이: 32바이트
    const int AES_KEY_LENGTH = 32;
    const int AES_BLOCK_SIZE = 16;
    
    // 키 생성: 제공된 키에서 필요한 길이만큼 사용
    result.key = (unsigned char*)malloc(AES_KEY_LENGTH);
    if (result.key == NULL) {
        return result;
    }
    
    // 제공된 키에서 AES_KEY_LENGTH 바이트 복사 (필요한 경우 패딩)
    size_t copy_len = (key_len < AES_KEY_LENGTH) ? key_len : AES_KEY_LENGTH;
    memcpy(result.key, key, copy_len);
    
    // 키가 충분하지 않으면 나머지를 0으로 채움
    if (copy_len < AES_KEY_LENGTH) {
        memset(result.key + copy_len, 0, AES_KEY_LENGTH - copy_len);
    }
    
    // IV 생성
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // 패딩을 위한 버퍼 크기 계산
    size_t padded_len = ((data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // 데이터 복사 및 PKCS#7 패딩 적용
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    memset(padded_data + data_len, pad_value, pad_value);
    
    // 암호화된 데이터 버퍼 할당
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        free(padded_data);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // AES 컨텍스트 초기화
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(padded_data);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // CBC 모드로 암호화
    unsigned char iv_copy[AES_BLOCK_SIZE];
    memcpy(iv_copy, result.iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                    &aes_key, iv_copy, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}