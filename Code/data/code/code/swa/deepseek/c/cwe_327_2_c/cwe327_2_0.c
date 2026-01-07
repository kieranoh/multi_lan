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
    
    // AES-256-CBC를 사용 (키 길이: 32바이트, IV 길이: 16바이트)
    const int aes_key_length = 32; // AES-256
    const int iv_length = 16;      // AES 블록 크기
    
    // 키 할당 및 복사 (제공된 키의 접두사 사용)
    result.key = (unsigned char*)malloc(aes_key_length);
    if (result.key == NULL) {
        return result;
    }
    
    // 제공된 키에서 필요한 만큼 복사 (부족하면 0으로 패딩)
    size_t copy_len = (key_len < aes_key_length) ? key_len : aes_key_length;
    memcpy(result.key, key, copy_len);
    
    // 키가 부족한 경우 나머지를 0으로 채움
    if (copy_len < aes_key_length) {
        memset(result.key + copy_len, 0, aes_key_length - copy_len);
    }
    
    // IV 할당 및 생성
    result.iv = (unsigned char*)malloc(iv_length);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // 암호학적으로 안전한 난수로 IV 생성
    if (RAND_bytes(result.iv, iv_length) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // AES 컨텍스트 초기화
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, aes_key_length * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // CBC 모드에서 PKCS#7 패딩을 위한 출력 버퍼 크기 계산
    // 패딩은 항상 추가되므로 (data_len / 16 + 1) * 16
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // 데이터 복사 및 PKCS#7 패딩 적용
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 패딩 적용
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // AES-CBC 암호화 수행
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                    &aes_key, result.iv, AES_ENCRYPT);
    
    // 임시 버퍼 정리
    free(padded_data);
    
    result.encrypted_len = padded_len;
    return result;
}