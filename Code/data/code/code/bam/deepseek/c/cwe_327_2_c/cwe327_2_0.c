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
    
    // AES-256-CBC를 사용 (제공된 키가 충분히 길다고 가정)
    // AES-256은 32바이트(256비트) 키를 필요로 함
    const int AES_KEY_SIZE = 32;
    const int AES_BLOCK_SIZE = 16;
    
    // IV 생성 (16바이트 for AES)
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!iv) {
        return result;
    }
    
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(iv);
        return result;
    }
    
    // 암호화 키 생성 (제공된 키의 접두사 사용)
    unsigned char* aes_key = (unsigned char*)malloc(AES_KEY_SIZE);
    if (!aes_key) {
        free(iv);
        return result;
    }
    
    // 제공된 키에서 AES 키 생성 (필요한 경우 패딩)
    size_t copy_len = (key_len < AES_KEY_SIZE) ? key_len : AES_KEY_SIZE;
    memcpy(aes_key, key, copy_len);
    
    // 키가 충분히 길지 않은 경우 나머지를 0으로 채움
    if (copy_len < AES_KEY_SIZE) {
        memset(aes_key + copy_len, 0, AES_KEY_SIZE - copy_len);
    }
    
    // 패딩을 위한 버퍼 크기 계산
    size_t padded_len = ((data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (!encrypted) {
        free(iv);
        free(aes_key);
        return result;
    }
    
    // AES 컨텍스트 설정
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key, 256, &aes_ctx) != 0) {
        free(iv);
        free(aes_key);
        free(encrypted);
        return result;
    }
    
    // 입력 데이터를 암호화 버퍼로 복사
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(iv);
        free(aes_key);
        free(encrypted);
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    // PKCS7 패딩 적용
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    memset(padded_data + data_len, pad_value, pad_value);
    
    // CBC 모드로 암호화
    unsigned char ivec[AES_BLOCK_SIZE];
    memcpy(ivec, iv, AES_BLOCK_SIZE);
    
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