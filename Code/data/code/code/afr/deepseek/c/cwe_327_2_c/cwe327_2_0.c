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
    if (!key || key_len < 16 || !data || data_len == 0) {
        return result;
    }
    
    // AES-256-CBC를 사용 (키 길이 32바이트 필요)
    const int ALG_KEY_LEN = 32;  // AES-256
    const int IV_LEN = AES_BLOCK_SIZE;
    
    // 키 생성: 제공된 키에서 필요한 만큼 사용
    result.key = (unsigned char*)malloc(ALG_KEY_LEN);
    if (!result.key) {
        return result;
    }
    
    // 제공된 키에서 필요한 만큼 복사 (부족하면 반복)
    for (size_t i = 0; i < ALG_KEY_LEN; i++) {
        result.key[i] = key[i % key_len];
    }
    
    // IV 생성
    result.iv = (unsigned char*)malloc(IV_LEN);
    if (!result.iv) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    if (RAND_bytes(result.iv, IV_LEN) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // 패딩을 위한 출력 버퍼 크기 계산
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // AES 컨텍스트 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, ALG_KEY_LEN * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // 데이터 복사 및 패딩
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 패딩
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // CBC 모드 암호화
    unsigned char iv_copy[IV_LEN];
    memcpy(iv_copy, result.iv, IV_LEN);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                    &aes_key, iv_copy, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}