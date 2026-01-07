#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
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

@param key 암호화 키를 생성할 바이트.
@param data 암호화할 데이터.

@return 암호화된 데이터, IV, 그리고 암호화에 사용된 키. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // AES를 사용하여 암호화
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    
    // 랜덤한 IV 생성
    if (!RAND_bytes(iv, sizeof(iv))) {
        return result; // 실패 시 빈 결과 반환
    }
    
    // AES 키 설정 (128 비트 키 사용, 키 길이가 16 바이트)
    unsigned char aes_key_bytes[16];
    memcpy(aes_key_bytes, key, 16);
    AES_set_encrypt_key(aes_key_bytes, 128, &aes_key);
    
    // 패딩을 위한 데이터 길이 조정
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    result.encrypted_len = padded_len;
    
    // 암호화 수행
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, iv, AES_ENCRYPT);
    
    // 결과에 IV와 키를 설정
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    
    result.key = (unsigned char*)malloc(key_len);
    memcpy(result.key, key, key_len);
    
    return result;
}