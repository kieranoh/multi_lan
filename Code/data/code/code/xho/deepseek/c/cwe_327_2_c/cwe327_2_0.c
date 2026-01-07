#include <openssl/evp.h>
#include <string.h>

encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    EVP_CIPHER_CTX *ctx = NULL;
    int len = 0, ciphertext_len = 0;
    
    // 알고리즘 선택: AES-256-CBC 사용 (제공된 키가 충분히 길다고 가정)
    const EVP_CIPHER *cipher = EVP_aes_256_cbc();
    int iv_len = EVP_CIPHER_iv_length(cipher);
    int key_required_len = EVP_CIPHER_key_length(cipher);
    
    // 키 길이 검증
    if (key_len < (size_t)key_required_len) {
        // 키가 너무 짧으면 실패
        return result;
    }
    
    // IV 할당 및 생성
    result.iv = (unsigned char*)malloc(iv_len);
    if (!result.iv) {
        return result;
    }
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    
    // 암호화 키 복사 (필요한 길이만큼)
    result.key = (unsigned char*)malloc(key_required_len);
    if (!result.key) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    memcpy(result.key, key, key_required_len);
    
    // 암호화된 데이터 버퍼 할당 (최대 크기: 데이터 길이 + 블록 크기)
    size_t max_encrypted_len = data_len + EVP_CIPHER_block_size(cipher);
    result.encrypted_data = (unsigned char*)malloc(max_encrypted_len);
    if (!result.encrypted_data) {
        free(result.iv);
        free(result.key);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // 암호화 컨텍스트 생성 및 초기화
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // 암호화 초기화
    if (EVP_EncryptInit_ex(ctx, cipher, NULL, result.key, result.iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // 데이터 암호화
    if (EVP_EncryptUpdate(ctx, result.encrypted_data, &len, data, data_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    ciphertext_len = len;
    
    // 최종 암호화 블록 처리
    if (EVP_EncryptFinal_ex(ctx, result.encrypted_data + ciphertext_len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    ciphertext_len += len;
    
    // 결과 설정
    result.encrypted_len = ciphertext_len;
    
    // 컨텍스트 정리
    EVP_CIPHER_CTX_free(ctx);
    
    return result;
}