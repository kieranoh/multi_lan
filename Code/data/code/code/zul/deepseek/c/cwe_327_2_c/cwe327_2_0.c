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
    
    // 1. 알고리즘 선택: AES-256-CBC 사용 (제공된 키 바이트 중 32바이트 사용)
    const EVP_CIPHER *cipher = EVP_aes_256_cbc();
    int required_key_len = EVP_CIPHER_key_length(cipher); // 32바이트
    int iv_len = EVP_CIPHER_iv_length(cipher); // 16바이트
    
    // 2. 키 길이 검증
    if (key_len < (size_t)required_key_len) {
        // 키가 너무 짧으면 실패
        return result;
    }
    
    // 3. 메모리 할당
    result.key = (unsigned char*)malloc(required_key_len);
    result.iv = (unsigned char*)malloc(iv_len);
    
    if (!result.key || !result.iv) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 4. 키 복사 (제공된 키의 처음 32바이트 사용)
    memcpy(result.key, key, required_key_len);
    
    // 5. IV 생성
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 6. 암호화된 데이터를 저장할 버퍼 할당
    // 최대 크기: 데이터 길이 + 블록 크기
    size_t max_encrypted_len = data_len + EVP_CIPHER_block_size(cipher);
    result.encrypted_data = (unsigned char*)malloc(max_encrypted_len);
    
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 7. 암호화 컨텍스트 생성 및 초기화
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        free(result.encrypted_data);
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 8. 암호화 초기화
    if (EVP_EncryptInit_ex(ctx, cipher, NULL, result.key, result.iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.encrypted_data);
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 9. 데이터 암호화
    if (EVP_EncryptUpdate(ctx, result.encrypted_data, &len, data, data_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.encrypted_data);
        free(result.key);
        free(result.iv);
        return result;
    }
    ciphertext_len = len;
    
    // 10. 최종 암호화 블록 처리
    if (EVP_EncryptFinal_ex(ctx, result.encrypted_data + ciphertext_len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.encrypted_data);
        free(result.key);
        free(result.iv);
        return result;
    }
    ciphertext_len += len;
    
    // 11. 결과 설정
    result.encrypted_len = ciphertext_len;
    
    // 12. 컨텍스트 정리
    EVP_CIPHER_CTX_free(ctx);
    
    return result;
}

// 사용 예시:
/*
int main() {
    // 테스트용 키와 데이터
    unsigned char key[64] = {0}; // 64바이트 키
    unsigned char data[] = "Hello, World!";
    size_t data_len = strlen((char*)data);
    
    // 키에 랜덤 값 채우기
    RAND_bytes(key, sizeof(key));
    
    // 데이터 암호화
    encryption_result result = encrypt_data(key, sizeof(key), data, data_len);
    
    if (result.encrypted_data) {
        printf("암호화 성공!\n");
        printf("암호화된 데이터 길이: %zu\n", result.encrypted_len);
        printf("IV 길이: 16\n");
        printf("키 길이: 32\n");
        
        // 메모리 해제
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
    } else {
        printf("암호화 실패!\n");
    }
    
    return 0;
}
*/