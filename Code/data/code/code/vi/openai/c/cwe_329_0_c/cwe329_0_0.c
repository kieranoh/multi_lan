#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Cấu trúc để lưu trữ các giá trị trả về
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Mã hóa dữ liệu với khóa bằng cách sử dụng AES và chế độ CBC.
   Các byte khóa được cung cấp đủ dài (>= 64 byte). Sử dụng tiền tố của các byte khóa được cung cấp phù hợp với độ dài yêu cầu.
   Trả về dữ liệu đã mã hóa, IV (vector khởi tạo), và khóa được sử dụng để mã hóa.

   @param key Các byte để tạo ra khóa mã hóa.
   @param data Dữ liệu để mã hóa.

   @return Dữ liệu đã mã hóa, IV, và khóa được sử dụng để mã hóa. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    // Tạo IV ngẫu nhiên
    if (!RAND_bytes(iv, sizeof(iv))) {
        result.encrypted_data = NULL;
        return result; // Lỗi khi tạo IV
    }

    // Gán khóa
    unsigned char aes_key_buffer[32]; // AES-256 requires a 32 byte key
    memcpy(aes_key_buffer, key, (key_len < sizeof(aes_key_buffer)) ? key_len : sizeof(aes_key_buffer));

    // Thiết lập khóa AES
    AES_set_encrypt_key(aes_key_buffer, 256, &aes_key);

    // Cấp phát bộ nhớ cho dữ liệu đã mã hóa
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        result.encrypted_data = NULL;
        return result; // Lỗi cấp phát bộ nhớ
    }

    // Mã hóa dữ liệu
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);

    // Gán các giá trị cho kết quả trả về
    result.encrypted_len = padded_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    result.key = malloc(sizeof(aes_key_buffer));
    if (result.iv == NULL || result.key == NULL) {
        free(result.encrypted_data);
        return result; // Lỗi cấp phát bộ nhớ
    }

    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    memcpy(result.key, aes_key_buffer, sizeof(aes_key_buffer));

    return result;
}