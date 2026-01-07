#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// 반환 값을 저장하는 구조체
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* AES와 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 충분히 깁니다(>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터), 그리고 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성하기 위한 바이트입니다.
@param data 암호화할 데이터입니다.

@return 암호화된 데이터, IV, 그리고 암호화에 사용된 키입니다. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    AES_KEY aes_key;
    
    // 입력 유효성 검사
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // AES-256-CBC를 사용 (256비트 = 32바이트)
    const int AES_KEY_SIZE = 32;
    const int IV_SIZE = AES_BLOCK_SIZE;
    
    // 키 할당 및 복사 (첫 32바이트 사용)
    result.key = (unsigned char*)malloc(AES_KEY_SIZE);
    if (result.key == NULL) {
        return result;
    }
    memcpy(result.key, key, AES_KEY_SIZE);
    
    // IV 할당 및 생성
    result.iv = (unsigned char*)malloc(IV_SIZE);
    if (result.iv == NULL) {
        free(result.key);
        return result;
    }
    
    // 암호학적으로 안전한 난수로 IV 생성
    if (RAND_bytes(result.iv, IV_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // AES 키 설정
    if (AES_set_encrypt_key(result.key, AES_KEY_SIZE * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // CBC 모드에서 패딩을 위한 출력 버퍼 크기 계산
    // PKCS#7 패딩: 최대 AES_BLOCK_SIZE 바이트 추가
    size_t padded_len = data_len + AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 실제 암호화 길이 저장
    result.encrypted_len = padded_len;
    
    // CBC 모드로 암호화
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, result.iv, AES_ENCRYPT);
    
    // 실제 암호화된 데이터 길이 조정
    // CBC 암호화는 입력 길이와 동일한 출력 길이를 생성
    result.encrypted_len = data_len;
    
    return result;
}