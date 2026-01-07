#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
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
    EVP_CIPHER_CTX *ctx = NULL;
    int len = 0, ciphertext_len = 0;
    
    // 1. 알고리즘 선택: AES-256-CBC 사용 (키 길이 32바이트 필요)
    const EVP_CIPHER *cipher = EVP_aes_256_cbc();
    int required_key_len = EVP_CIPHER_key_length(cipher); // 32바이트
    int iv_len = EVP_CIPHER_iv_length(cipher); // 16바이트
    
    // 2. 키 생성: 제공된 키에서 필요한 만큼만 사용
    result.key = (unsigned char*)malloc(required_key_len);
    if (!result.key) goto cleanup;
    
    // 키 바이트가 충분하지 않으면 0으로 패딩
    if (key_len >= required_key_len) {
        memcpy(result.key, key, required_key_len);
    } else {
        memcpy(result.key, key, key_len);
        memset(result.key + key_len, 0, required_key_len - key_len);
    }
    
    // 3. IV 생성
    result.iv = (unsigned char*)malloc(iv_len);
    if (!result.iv) goto cleanup;
    
    if (RAND_bytes(result.iv, iv_len) != 1) {
        goto cleanup;
    }
    
    // 4. 암호화 컨텍스트 생성 및 초기화
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) goto cleanup;
    
    if (EVP_EncryptInit_ex(ctx, cipher, NULL, result.key, result.iv) != 1) {
        goto cleanup;
    }
    
    // 5. 암호화된 데이터 버퍼 할당 (최대 크기: 데이터 길이 + 블록 크기)
    result.encrypted_data = (unsigned char*)malloc(data_len + EVP_CIPHER_block_size(cipher));
    if (!result.encrypted_data) goto cleanup;
    
    // 6. 데이터 암호화
    if (EVP_EncryptUpdate(ctx, result.encrypted_data, &len, data, data_len) != 1) {
        goto cleanup;
    }
    ciphertext_len = len;
    
    // 7. 최종 블록 처리
    if (EVP_EncryptFinal_ex(ctx, result.encrypted_data + len, &len) != 1) {
        goto cleanup;
    }
    ciphertext_len += len;
    
    result.encrypted_len = ciphertext_len;
    
    // 성공 시 컨텍스트 정리
    if (ctx) EVP_CIPHER_CTX_free(ctx);
    return result;
    
cleanup:
    // 실패 시 메모리 정리
    if (result.key) free(result.key);
    if (result.iv) free(result.iv);
    if (result.encrypted_data) free(result.encrypted_data);
    if (ctx) EVP_CIPHER_CTX_free(ctx);
    
    // 실패 시 모든 필드를 NULL로 설정
    result.key = NULL;
    result.iv = NULL;
    result.encrypted_data = NULL;
    result.encrypted_len = 0;
    
    return result;
}