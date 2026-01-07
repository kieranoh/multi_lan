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
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);
    
    // Generate a random IV
    if (!RAND_bytes(result.iv, AES_BLOCK_SIZE)) {
        // Handle error
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }

    // Use the first 16 bytes of the key for AES
    unsigned char aes_key[16]; // AES-128
    memcpy(aes_key, key, 16);
    
    AES_KEY enc_key;
    if (AES_set_encrypt_key(aes_key, 128, &enc_key) < 0) {
        // Handle error
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }

    size_t padded_len = ((data_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    
    // PKCS#7 padding
    memcpy(padded_data, data, data_len);
    size_t padding_needed = padded_len - data_len;
    memset(padded_data + data_len, padding_needed, padding_needed);

    // Encrypt
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &enc_key, result.iv, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;

    // Copy the key (for demonstration, it's not secured)
    memcpy(result.key, aes_key, key_len);

    free(padded_data);
    
    return result;
}