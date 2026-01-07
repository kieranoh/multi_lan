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
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    
    // Generate random IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Use the first 32 bytes of the key (for AES-256)
    unsigned char key_buffer[32];
    memset(key_buffer, 0, sizeof(key_buffer));
    memcpy(key_buffer, key, key_len < sizeof(key_buffer) ? key_len : sizeof(key_buffer));

    // Set encryption key
    AES_set_encrypt_key(key_buffer, 256, &aes_key);

    // Calculate the size of the padded data
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    // Allocate memory for encrypted data
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    memset(result.encrypted_data, 0, padded_len);
    
    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, iv, AES_ENCRYPT);

    // Set the result values
    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(32);
    memcpy(result.key, key_buffer, 32);

    return result;
}