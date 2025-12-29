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
    
    // AES-256-CBC를 사용 (제공된 키는 충분히 길다고 가정)
    const int algorithm_key_len = 32; // AES-256 키 길이
    const int iv_len = AES_BLOCK_SIZE; // AES 블록 크기
    
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
    
    // 키 할당 및 복사 (제공된 키의 접두사 사용)
    result.key = (unsigned char*)malloc(algorithm_key_len);
    if (!result.key) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    
    // 제공된 키에서 필요한 만큼 복사 (안전하게)
    size_t copy_len = (key_len < algorithm_key_len) ? key_len : algorithm_key_len;
    memcpy(result.key, key, copy_len);
    
    // 키가 충분히 길지 않으면 나머지를 0으로 채움
    if (copy_len < algorithm_key_len) {
        memset(result.key + copy_len, 0, algorithm_key_len - copy_len);
    }
    
    // 패딩을 위한 암호화된 데이터 버퍼 크기 계산
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(result.iv);
        free(result.key);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // 데이터 복사 (나중에 암호화할 때 수정됨)
    memcpy(result.encrypted_data, data, data_len);
    
    // AES 컨텍스트 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, algorithm_key_len * 8, &aes_key) != 0) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // CBC 모드로 암호화
    unsigned char ivec[AES_BLOCK_SIZE];
    memcpy(ivec, result.iv, AES_BLOCK_SIZE);
    
    // 암호화 수행
    AES_cbc_encrypt(result.encrypted_data, result.encrypted_data, padded_len, 
                    &aes_key, ivec, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    return result;
}