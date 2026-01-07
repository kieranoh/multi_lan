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
    if (key == NULL || data == NULL || key_len < 16 || data_len == 0) {
        return result;
    }
    
    // AES-256-CBC를 사용 (제공된 키가 충분히 길다고 가정)
    // AES-256은 32바이트(256비트) 키를 필요로 함
    const int aes_key_length = 32;
    const int iv_length = AES_BLOCK_SIZE; // 16바이트
    
    // IV 생성
    unsigned char* iv = (unsigned char*)malloc(iv_length);
    if (iv == NULL) {
        return result;
    }
    
    if (RAND_bytes(iv, iv_length) != 1) {
        free(iv);
        return result;
    }
    
    // 키 복사 (제공된 키에서 첫 32바이트 사용)
    unsigned char* aes_key = (unsigned char*)malloc(aes_key_length);
    if (aes_key == NULL) {
        free(iv);
        return result;
    }
    
    // 제공된 키에서 필요한 만큼 복사 (제공된 키가 더 짧을 경우 0으로 패딩)
    size_t copy_len = (key_len < aes_key_length) ? key_len : aes_key_length;
    memcpy(aes_key, key, copy_len);
    
    // 제공된 키가 더 짧을 경우 나머지를 0으로 채움
    if (copy_len < aes_key_length) {
        memset(aes_key + copy_len, 0, aes_key_length - copy_len);
    }
    
    // 패딩을 위한 공간 계산
    size_t padded_len = ((data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(iv);
        free(aes_key);
        return result;
    }
    
    // 데이터 복사 및 PKCS#7 패딩 적용
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 패딩
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // 암호화된 데이터 저장을 위한 메모리 할당
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (encrypted == NULL) {
        free(iv);
        free(aes_key);
        free(padded_data);
        return result;
    }
    
    // AES 컨텍스트 초기화
    AES_KEY aes_key_struct;
    if (AES_set_encrypt_key(aes_key, 256, &aes_key_struct) != 0) {
        free(iv);
        free(aes_key);
        free(padded_data);
        free(encrypted);
        return result;
    }
    
    // CBC 모드로 암호화
    unsigned char ivec[AES_BLOCK_SIZE];
    memcpy(ivec, iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_key_struct, ivec, AES_ENCRYPT);
    
    // 결과 구조체 채우기
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = aes_key;
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}