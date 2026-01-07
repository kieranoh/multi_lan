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
    
    // AES-256-CBC를 사용 (주석에 명시된 대로 하나의 알고리즘 선택)
    // 키 접두사 32바이트(256비트) 사용
    const size_t aes_key_len = 32;
    const size_t iv_len = AES_BLOCK_SIZE;
    
    // 결과 구조체 초기화
    result.key = (unsigned char*)malloc(aes_key_len);
    result.iv = (unsigned char*)malloc(iv_len);
    
    if (!result.key || !result.iv) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 제공된 키에서 AES 키 생성 (접두사 사용)
    memcpy(result.key, key, aes_key_len > key_len ? key_len : aes_key_len);
    if (aes_key_len > key_len) {
        // 키가 충분히 길지 않으면 나머지를 0으로 채움
        memset(result.key + key_len, 0, aes_key_len - key_len);
    }
    
    // IV 생성
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 패딩을 위한 버퍼 크기 계산
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // AES 컨텍스트 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }
    
    // 데이터 복사 (실제 암호화는 in-place로 수행됨)
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    // PKCS#7 패딩 적용
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    memset(padded_data + data_len, pad_value, pad_value);
    
    // CBC 모드로 암호화
    unsigned char iv_copy[AES_BLOCK_SIZE];
    memcpy(iv_copy, result.iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                    &aes_key, iv_copy, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}