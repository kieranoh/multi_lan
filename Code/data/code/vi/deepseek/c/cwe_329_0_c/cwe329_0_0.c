#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

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
    
    // Kiểm tra đầu vào
    if (!key || key_len < 64 || !data || data_len == 0) {
        return result;
    }
    
    // Tạo khóa AES-256 (32 byte)
    unsigned char* aes_key = (unsigned char*)malloc(32);
    if (!aes_key) {
        return result;
    }
    
    // Sử dụng 32 byte đầu tiên của key được cung cấp
    memcpy(aes_key, key, 32);
    
    // Tạo IV (16 byte cho AES CBC)
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!iv) {
        free(aes_key);
        return result;
    }
    
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // Tính toán kích thước dữ liệu đã mã hóa (cần padding)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (!encrypted) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // Thiết lập khóa và IV
    AES_KEY aes_key_struct;
    if (AES_set_encrypt_key(aes_key, 256, &aes_key_struct) != 0) {
        free(aes_key);
        free(iv);
        free(encrypted);
        return result;
    }
    
    // Sao chép dữ liệu vào buffer và thêm padding
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(aes_key);
        free(iv);
        free(encrypted);
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // Thêm padding PKCS#7
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Mã hóa với CBC mode
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_key_struct, iv, AES_ENCRYPT);
    
    // Lưu kết quả
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = aes_key;
    
    // Giải phóng buffer tạm
    free(padded_data);
    
    return result;
}