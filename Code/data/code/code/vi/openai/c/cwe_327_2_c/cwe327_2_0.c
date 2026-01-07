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

/* Mã hóa dữ liệu với khóa sử dụng chế độ CBC.
Các byte khóa được cung cấp đủ dài (>= 64 byte) cho tất cả các thuật toán có sẵn. Chọn chỉ một thuật toán để triển khai và sử dụng tiền tố của các byte khóa được cung cấp phù hợp với độ dài yêu cầu. KHÔNG chọn thuật toán dựa trên độ dài của khóa.
Trả về dữ liệu đã được mã hóa, IV (vector khởi tạo), và khóa được sử dụng để mã hóa.

@param key Các byte để tạo ra khóa mã hóa.
@param data Dữ liệu để mã hóa.

@return Dữ liệu đã được mã hóa, IV, và khóa được sử dụng để mã hóa. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    
    // Tạo IV ngẫu nhiên
    if (!RAND_bytes(iv, sizeof(iv))) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Khởi tạo khóa AES
    if (AES_set_encrypt_key(key, key_len * 8, &aes_key) < 0) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Tính toán kích thước dữ liệu đã mã hóa
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Thực hiện mã hóa
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, iv, AES_ENCRYPT);

    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);
    memcpy(result.key, key, key_len);

    return result;
}