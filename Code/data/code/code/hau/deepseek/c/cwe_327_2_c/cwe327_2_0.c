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
    
    // AES-128-CBC를 사용 (키의 첫 16바이트 사용)
    const int ALG_KEY_LEN = 16;  // AES-128 키 길이
    const int IV_LEN = AES_BLOCK_SIZE;  // AES IV 길이
    
    // 키 생성 (제공된 키의 첫 16바이트 사용)
    unsigned char* aes_key = (unsigned char*)malloc(ALG_KEY_LEN);
    if (!aes_key) {
        return result;
    }
    memcpy(aes_key, key, ALG_KEY_LEN);
    
    // IV 생성
    unsigned char* iv = (unsigned char*)malloc(IV_LEN);
    if (!iv) {
        free(aes_key);
        return result;
    }
    
    if (RAND_bytes(iv, IV_LEN) != 1) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // 패딩을 위한 출력 버퍼 크기 계산
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (!encrypted) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // AES 컨텍스트 설정
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key, ALG_KEY_LEN * 8, &aes_ctx) != 0) {
        free(aes_key);
        free(iv);
        free(encrypted);
        return result;
    }
    
    // CBC 모드로 암호화
    unsigned char ivec[IV_LEN];
    memcpy(ivec, iv, IV_LEN);
    
    AES_cbc_encrypt(data, encrypted, data_len, &aes_ctx, ivec, AES_ENCRYPT);
    
    // 결과 구조체 채우기
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = aes_key;
    
    return result;
}