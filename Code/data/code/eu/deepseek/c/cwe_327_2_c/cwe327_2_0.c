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
    
    // Algoritmoa aukeratu (AES-256-CBC bakarrik)
    const int algorithm_key_len = 32; // AES-256-rentzako 32 byte (256 bit)
    const int iv_len = AES_BLOCK_SIZE; // AES-rentzako IV luzera
    
    // Gakoa kopiatu (aurreko 32 byte bakarrik erabiliz)
    result.key = (unsigned char*)malloc(algorithm_key_len);
    if (!result.key) {
        return result;
    }
    
    // Gakoaren aurrefiksoa kopiatu (32 byte)
    size_t copy_len = key_len < algorithm_key_len ? key_len : algorithm_key_len;
    memcpy(result.key, key, copy_len);
    
    // Gakoa bete behar bada
    if (copy_len < algorithm_key_len) {
        memset(result.key + copy_len, 0, algorithm_key_len - copy_len);
    }
    
    // IV sortu
    result.iv = (unsigned char*)malloc(iv_len);
    if (!result.iv) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Datuak enkriptatzeko prestatu (CBC moduan padding behar du)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // AES kontextua hasieratu
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, algorithm_key_len * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Datuak enkriptatu CBC moduan
    unsigned char ivec[AES_BLOCK_SIZE];
    memcpy(ivec, result.iv, AES_BLOCK_SIZE);
    
    // Datuen kopia bat egin padding-arekin
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
    
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 padding aplikatu
    unsigned char pad_value = padded_len - data_len;
    memset(padded_data + data_len, pad_value, pad_value);
    
    // CBC enkriptazioa
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, ivec, AES_ENCRYPT);
    
    free(padded_data);
    
    result.encrypted_len = padded_len;
    return result;
}