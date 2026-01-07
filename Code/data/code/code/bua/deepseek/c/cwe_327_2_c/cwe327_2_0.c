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
    if (!key || key_len == 0 || !data || data_len == 0) {
        return result;
    }
    
    // AES-256-CBC를 사용 (제공된 키가 충분히 길다고 가정)
    // AES-256은 32바이트 키를 필요로 함
    const int AES_KEY_SIZE = 32;
    const int AES_IV_SIZE = AES_BLOCK_SIZE;
    
    // 키가 충분히 긴지 확인
    if (key_len < AES_KEY_SIZE) {
        return result;
    }
    
    // IV 할당 및 생성
    result.iv = (unsigned char*)malloc(AES_IV_SIZE);
    if (!result.iv) {
        return result;
    }
    
    // 랜덤 IV 생성
    if (RAND_bytes(result.iv, AES_IV_SIZE) != 1) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    
    // 암호화 키 할당 및 복사 (AES-256에 필요한 32바이트만 사용)
    result.key = (unsigned char*)malloc(AES_KEY_SIZE);
    if (!result.key) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    memcpy(result.key, key, AES_KEY_SIZE);
    
    // AES 컨텍스트 초기화
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(result.iv);
        free(result.key);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // CBC 모드에서 필요한 패딩 계산
    // PKCS#7 패딩: 블록 크기의 배수로 만들기 위해 필요한 바이트 수 추가
    size_t padded_len = data_len + (AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));
    
    // 암호화된 데이터 버퍼 할당
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(result.iv);
        free(result.key);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // 입력 데이터를 패딩된 버퍼로 복사
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 패딩 적용
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // CBC 모드로 암호화 수행
    unsigned char iv_copy[AES_IV_SIZE];
    memcpy(iv_copy, result.iv, AES_IV_SIZE);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                    &aes_key, iv_copy, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}