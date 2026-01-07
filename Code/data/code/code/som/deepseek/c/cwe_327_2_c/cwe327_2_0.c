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
    
    // AES-256-CBC를 사용 (제공된 키 바이트의 접두사 사용)
    const int ALGORITHM_KEY_LENGTH = 32; // AES-256
    const int IV_LENGTH = AES_BLOCK_SIZE;
    
    // 결과 구조체 초기화
    result.key = (unsigned char*)malloc(ALGORITHM_KEY_LENGTH);
    result.iv = (unsigned char*)malloc(IV_LENGTH);
    
    if (result.key == NULL || result.iv == NULL) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 제공된 키에서 필요한 길이만큼 접두사 복사
    size_t copy_len = (key_len < ALGORITHM_KEY_LENGTH) ? key_len : ALGORITHM_KEY_LENGTH;
    memcpy(result.key, key, copy_len);
    
    // 키 길이가 부족한 경우 나머지를 0으로 채움
    if (copy_len < ALGORITHM_KEY_LENGTH) {
        memset(result.key + copy_len, 0, ALGORITHM_KEY_LENGTH - copy_len);
    }
    
    // IV 생성
    if (RAND_bytes(result.iv, IV_LENGTH) != 1) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 패딩을 위한 공간 계산
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // AES 컨텍스트 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, ALGORITHM_KEY_LENGTH * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }
    
    // 데이터 복사 (실제 암호화는 CBC 모드에서 수행)
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }
    
    // 원본 데이터 복사 및 PKCS#7 패딩 적용
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    memset(padded_data + data_len, pad_value, pad_value);
    
    // CBC 모드 암호화
    unsigned char ivec[IV_LENGTH];
    memcpy(ivec, result.iv, IV_LENGTH);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, ivec, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}