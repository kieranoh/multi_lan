#include <openssl/aes.h>
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
    
    // Gakoa prestatu (AES-256 erabiltzeko 32 byte)
    const size_t aes_key_len = 32; // AES-256
    unsigned char* derived_key = (unsigned char*)malloc(aes_key_len);
    if (!derived_key) {
        return result;
    }
    
    // Emandako gakoaren aurprefikoa erabili (gutxienez 64 byte eskatzen dira)
    if (key_len < 64) {
        free(derived_key);
        return result;
    }
    
    // Lehenengo 32 byte hartu AES-256 gako gisa
    memcpy(derived_key, key, aes_key_len);
    
    // IV sortu (16 byte AES-CBC-rako)
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!iv) {
        free(derived_key);
        return result;
    }
    
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(derived_key);
        free(iv);
        return result;
    }
    
    // Datuak enkriptatzeko bufferra prestatu
    // Datuak bloke tamainan lerrokatuta egon behar dute
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(derived_key);
        free(iv);
        return result;
    }
    
    // Datuak kopiatu eta PKCS#7 padding aplikatu
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = padded_len - data_len;
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Enkriptatutako datuentzako memoria
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (!encrypted) {
        free(derived_key);
        free(iv);
        free(padded_data);
        return result;
    }
    
    // AES kontextua prestatu
    AES_KEY aes_key;
    if (AES_set_encrypt_key(derived_key, 256, &aes_key) != 0) {
        free(derived_key);
        free(iv);
        free(padded_data);
        free(encrypted);
        return result;
    }
    
    // Datuak enkriptatu CBC moduan
    unsigned char ivec[AES_BLOCK_SIZE];
    memcpy(ivec, iv, AES_BLOCK_SIZE);
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_key, ivec, AES_ENCRYPT);
    
    // Emaitzak gorde
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = derived_key;
    
    // Behin behineko bufferrak garbitu
    free(padded_data);
    
    return result;
}