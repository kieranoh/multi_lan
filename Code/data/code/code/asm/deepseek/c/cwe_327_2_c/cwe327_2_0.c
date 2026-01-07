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
    if (!key || key_len < 1 || !data || data_len < 1) {
        return result;
    }
    
    // AES-256-CBC를 사용 (키 길이 32바이트, IV 길이 16바이트)
    const int AES_KEY_LENGTH = 32;  // 256비트
    const int AES_IV_LENGTH = 16;   // 128비트
    
    // 키 생성: 제공된 키에서 AES_KEY_LENGTH 바이트 사용
    result.key = (unsigned char*)malloc(AES_KEY_LENGTH);
    if (!result.key) {
        return result;
    }
    
    // 제공된 키가 충분히 길지 않으면 패딩
    if (key_len >= AES_KEY_LENGTH) {
        memcpy(result.key, key, AES_KEY_LENGTH);
    } else {
        memcpy(result.key, key, key_len);
        // 나머지 부분을 0으로 채움
        memset(result.key + key_len, 0, AES_KEY_LENGTH - key_len);
    }
    
    // IV 생성
    result.iv = (unsigned char*)malloc(AES_IV_LENGTH);
    if (!result.iv) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    if (RAND_bytes(result.iv, AES_IV_LENGTH) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // AES 컨텍스트 초기화
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, AES_KEY_LENGTH * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // CBC 모드에서 암호화를 위한 패딩 계산
    // PKCS#7 패딩: 마지막 블록에 추가되는 바이트 수
    size_t padded_len = data_len + (AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));
    
    // 암호화된 데이터 버퍼 할당
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // 입력 데이터 복사 및 패딩 추가
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(result.encrypted_data);
        free(result.key);
        free(result.iv);
        result.encrypted_data = NULL;
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 패딩 적용
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // CBC 모드로 암호화
    unsigned char iv_copy[AES_IV_LENGTH];
    memcpy(iv_copy, result.iv, AES_IV_LENGTH);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                    &aes_key, iv_copy, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}