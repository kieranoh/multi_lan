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
    
    // AES-256-CBC를 사용 (제공된 키가 충분히 길다고 가정)
    const int ALGORITHM_KEY_LENGTH = 32; // AES-256
    const int IV_LENGTH = AES_BLOCK_SIZE;
    
    // 키 할당 및 복사
    result.key = (unsigned char*)malloc(ALGORITHM_KEY_LENGTH);
    if (!result.key) {
        return result;
    }
    
    // 제공된 키에서 필요한 만큼만 사용 (접두사)
    size_t copy_len = key_len < ALGORITHM_KEY_LENGTH ? key_len : ALGORITHM_KEY_LENGTH;
    memcpy(result.key, key, copy_len);
    
    // 키 길이가 부족한 경우 나머지를 0으로 채움
    if (copy_len < ALGORITHM_KEY_LENGTH) {
        memset(result.key + copy_len, 0, ALGORITHM_KEY_LENGTH - copy_len);
    }
    
    // IV 할당 및 생성
    result.iv = (unsigned char*)malloc(IV_LENGTH);
    if (!result.iv) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    if (RAND_bytes(result.iv, IV_LENGTH) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // 패딩을 위한 출력 버퍼 크기 계산
    size_t padded_len = data_len + (AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // AES 컨텍스트 초기화
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, ALGORITHM_KEY_LENGTH * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // CBC 모드로 암호화
    unsigned char ivec[IV_LENGTH];
    memcpy(ivec, result.iv, IV_LENGTH);
    
    // 입력 데이터를 그대로 암호화 (OpenSSL이 자동으로 PKCS#7 패딩을 추가)
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, ivec, AES_ENCRYPT);
    
    // 암호화된 데이터 길이 설정 (CBC 모드에서 입력 길이와 동일)
    result.encrypted_len = padded_len;
    
    return result;
}