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
    
    // AES-256-CBC를 사용 (제공된 키 바이트가 충분히 길다고 가정)
    const int algorithm_key_len = 32; // AES-256 키 길이
    const int iv_len = AES_BLOCK_SIZE; // AES 블록 크기
    
    // 결과 구조체 초기화
    result.iv = (unsigned char*)malloc(iv_len);
    result.key = (unsigned char*)malloc(algorithm_key_len);
    
    if (result.iv == NULL || result.key == NULL) {
        free(result.iv);
        free(result.key);
        return result;
    }
    
    // IV 생성
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.iv);
        free(result.key);
        return result;
    }
    
    // 키 복사 (제공된 키의 접두사 사용)
    size_t copy_len = key_len < algorithm_key_len ? key_len : algorithm_key_len;
    memcpy(result.key, key, copy_len);
    
    // 키 길이가 부족한 경우 나머지를 0으로 채움
    if (copy_len < algorithm_key_len) {
        memset(result.key + copy_len, 0, algorithm_key_len - copy_len);
    }
    
    // 패딩을 위한 출력 버퍼 크기 계산
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    
    if (result.encrypted_data == NULL) {
        free(result.iv);
        free(result.key);
        return result;
    }
    
    // AES 컨텍스트 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, algorithm_key_len * 8, &aes_key) != 0) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        return result;
    }
    
    // 데이터 암호화
    unsigned char iv_copy[iv_len];
    memcpy(iv_copy, result.iv, iv_len);
    
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, iv_copy, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    return result;
}