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
    
    // AES-256-CBC를 사용 (제공된 키 바이트에서 접두사 사용)
    // AES-256은 32바이트 키가 필요함
    const int AES_KEY_SIZE = 32;
    const int AES_IV_SIZE = AES_BLOCK_SIZE;
    
    // 키가 충분히 긴지 확인
    if (key_len < AES_KEY_SIZE) {
        return result;
    }
    
    // 결과 구조체 초기화
    result.key = (unsigned char*)malloc(AES_KEY_SIZE);
    result.iv = (unsigned char*)malloc(AES_IV_SIZE);
    
    if (!result.key || !result.iv) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 제공된 키에서 AES-256 키로 접두사 사용
    memcpy(result.key, key, AES_KEY_SIZE);
    
    // 랜덤 IV 생성
    if (RAND_bytes(result.iv, AES_IV_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 패딩을 위한 공간 계산
    // CBC 모드에서는 PKCS#7 패딩이 사용됨
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // AES 컨텍스트 초기화
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }
    
    // 데이터 암호화
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, result.iv, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    return result;
}