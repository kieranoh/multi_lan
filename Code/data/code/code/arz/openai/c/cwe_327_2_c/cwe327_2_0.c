#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>

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
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);
    
    // 키의 접미사를 사용하여 AES_KEY 설정
    memcpy(result.key, key, key_len);
    
    // IV를 랜덤하게 생성
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        // 오류 처리: 랜덤 바이트 생성 실패
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result;
    }
    
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    
    // AES 암호화 키 설정
    AES_set_encrypt_key(result.key, key_len * 8, &aes_key);

    // 데이터 암호화
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;

    return result;
}