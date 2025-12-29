#include <openssl/aes.h>
#include <openssl/des.h>
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
    
    // Kiểm tra đầu vào hợp lệ
    if (!key || key_len < 16 || !data || data_len == 0) {
        return result;
    }
    
    // Chọn AES-256-CBC (sử dụng 32 byte đầu tiên của key)
    const int algorithm_key_len = 32; // AES-256
    const int iv_len = AES_BLOCK_SIZE;
    
    // Cấp phát bộ nhớ cho key được sử dụng
    result.key = (unsigned char*)malloc(algorithm_key_len);
    if (!result.key) {
        return result;
    }
    
    // Sao chép 32 byte đầu tiên từ key được cung cấp
    memcpy(result.key, key, algorithm_key_len);
    
    // Cấp phát bộ nhớ cho IV
    result.iv = (unsigned char*)malloc(iv_len);
    if (!result.iv) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Tạo IV ngẫu nhiên
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Tính toán kích thước dữ liệu đã mã hóa (thêm padding)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Khởi tạo context AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Tạo bản sao của dữ liệu để thêm padding
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Sao chép dữ liệu và thêm padding PKCS#7
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = padded_len - data_len;
    memset(padded_data + data_len, pad_value, pad_value);
    
    // Mã hóa dữ liệu với AES-256-CBC
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    
    // Lưu kích thước dữ liệu đã mã hóa
    result.encrypted_len = padded_len;
    
    // Giải phóng bộ nhớ tạm
    free(padded_data);
    
    return result;
}