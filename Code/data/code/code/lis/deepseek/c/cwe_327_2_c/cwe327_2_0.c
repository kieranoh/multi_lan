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
    if (key == NULL || data == NULL || key_len == 0 || data_len == 0) {
        return result;
    }
    
    // AES-256-CBC를 사용 (제공된 키가 충분히 길다고 가정)
    // AES-256은 32바이트 키가 필요함
    const int aes_key_length = 32;
    const int iv_length = AES_BLOCK_SIZE;
    
    // 키 할당 및 복사 (필요한 만큼만 사용)
    result.key = (unsigned char*)malloc(aes_key_length);
    if (result.key == NULL) {
        return result;
    }
    
    // 제공된 키에서 필요한 만큼 복사 (패딩이 필요한 경우 0으로 패딩)
    size_t copy_len = (key_len < aes_key_length) ? key_len : aes_key_length;
    memcpy(result.key, key, copy_len);
    
    // 키가 더 짧은 경우 나머지를 0으로 채움
    if (copy_len < aes_key_length) {
        memset(result.key + copy_len, 0, aes_key_length - copy_len);
    }
    
    // IV 할당 및 생성
    result.iv = (unsigned char*)malloc(iv_length);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // 암호학적으로 안전한 난수로 IV 생성
    if (RAND_bytes(result.iv, iv_length) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // AES 컨텍스트 초기화
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, aes_key_length * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // CBC 모드에서 암호화를 위해 패딩이 필요함
    // PKCS#7 패딩: 최대 AES_BLOCK_SIZE 바이트까지 패딩
    size_t padded_len = data_len + (AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));
    
    // 암호화된 데이터 버퍼 할당
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // 데이터 복사 및 PKCS#7 패딩 적용
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 패딩 적용
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // AES CBC 모드 암호화
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    
    // 임시 버퍼 정리
    free(padded_data);
    
    // 결과 설정
    result.encrypted_len = padded_len;
    
    return result;
}