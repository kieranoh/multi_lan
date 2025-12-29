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
    encryption_result result;
    result.encrypted_data = NULL;
    result.encrypted_len = 0;
    result.iv = NULL;
    result.key = NULL;
    
    // Provjeri ulazne parametre
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // Koristimo AES-256-CBC (32 bajta = 256 bita)
    const int AES_KEY_LENGTH = 32;
    
    // Alociraj i kopiraj ključ (prvih 32 bajta iz ulaznog ključa)
    result.key = (unsigned char*)malloc(AES_KEY_LENGTH);
    if (result.key == NULL) {
        return result;
    }
    memcpy(result.key, key, AES_KEY_LENGTH);
    
    // Alociraj IV (16 bajta za AES blok)
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Generiraj sigurni IV
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Pripremi AES kontekst
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, AES_KEY_LENGTH * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Izračunaj veličinu za šifrirane podatke (zaokruženo na viši AES blok)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Kopiraj originalne podatke u buffer za padding
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
    
    // Primijeni PKCS#7 padding
    unsigned char pad_value = padded_len - data_len;
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Šifriraj podatke koristeći AES-CBC
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    
    // Postavi duljinu šifriranih podataka
    result.encrypted_len = padded_len;
    
    // Očisti privremene podatke
    free(padded_data);
    
    return result;
}