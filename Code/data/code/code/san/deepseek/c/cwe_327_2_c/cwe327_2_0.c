#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

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
    if (!key || key_len == 0 || !data || data_len == 0) {
        return result;
    }
    
    // AES-256-CBC를 사용 (제공된 키가 충분히 길다고 가정)
    // AES-256은 32바이트 키를 필요로 함
    const int aes_key_length = 32;
    const int iv_length = AES_BLOCK_SIZE;
    
    // 키가 충분히 긴지 확인
    if (key_len < aes_key_length) {
        return result;
    }
    
    // 메모리 할당
    result.key = (unsigned char*)malloc(aes_key_length);
    result.iv = (unsigned char*)malloc(iv_length);
    
    if (!result.key || !result.iv) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 키 복사 (제공된 키의 첫 32바이트 사용)
    memcpy(result.key, key, aes_key_length);
    
    // 랜덤 IV 생성
    if (RAND_bytes(result.iv, iv_length) != 1) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 패딩을 위한 공간 계산
    // CBC 모드에서는 PKCS#7 패딩 사용
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // AES 컨텍스트 초기화
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, aes_key_length * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }
    
    // 데이터 암호화
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }
    
    // 원본 데이터 복사 및 패딩 추가
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 패딩 추가
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // CBC 모드로 암호화
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                    &aes_key, result.iv, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}