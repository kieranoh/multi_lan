#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <string.h>
#include <stdlib.h>

// 반환 값을 저장할 구조체
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 모든 사용 가능한 알고리즘에 대해 충분히 깁니다(>= 64 바이트). 구현할 알고리즘을 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 키의 길이에 따라 알고리즘을 선택하지 마세요.
암호화된 데이터, IV(초기화 벡터), 그리고 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성하기 위한 바이트입니다.
@param data 암호화할 데이터입니다.

@return 암호화된 데이터, IV, 그리고 암호화에 사용된 키입니다. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    EVP_CIPHER_CTX *ctx = NULL;
    int len = 0, ciphertext_len = 0;
    
    // AES-256-CBC를 사용 (키 길이: 32바이트, IV 길이: 16바이트)
    const EVP_CIPHER *cipher = EVP_aes_256_cbc();
    const int key_size = 32; // AES-256 키 길이
    const int iv_size = EVP_CIPHER_iv_length(cipher);
    
    // 메모리 할당 실패 확인
    if (key_len < key_size) {
        // 키가 충분히 길지 않으면 빈 결과 반환
        return result;
    }
    
    // 결과 구조체 초기화
    result.key = (unsigned char*)malloc(key_size);
    result.iv = (unsigned char*)malloc(iv_size);
    if (!result.key || !result.iv) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 키 복사 (제공된 키의 첫 32바이트 사용)
    memcpy(result.key, key, key_size);
    
    // IV 생성
    if (RAND_bytes(result.iv, iv_size) != 1) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 암호화된 데이터를 저장할 버퍼 할당 (패딩을 고려하여 추가 공간)
    result.encrypted_data = (unsigned char*)malloc(data_len + EVP_MAX_BLOCK_LENGTH);
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 암호화 컨텍스트 생성 및 초기화
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        return result;
    }
    
    // 암호화 초기화
    if (EVP_EncryptInit_ex(ctx, cipher, NULL, result.key, result.iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        return result;
    }
    
    // 데이터 암호화
    if (EVP_EncryptUpdate(ctx, result.encrypted_data, &len, data, data_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        return result;
    }
    ciphertext_len = len;
    
    // 최종 블록 처리 (패딩)
    if (EVP_EncryptFinal_ex(ctx, result.encrypted_data + ciphertext_len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        return result;
    }
    ciphertext_len += len;
    
    // 암호화된 데이터 길이 설정
    result.encrypted_len = ciphertext_len;
    
    // 컨텍스트 정리
    EVP_CIPHER_CTX_free(ctx);
    
    return result;
}