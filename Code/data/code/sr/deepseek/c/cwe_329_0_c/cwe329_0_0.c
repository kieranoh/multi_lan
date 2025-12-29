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
    
    // Provera ulaznih parametara
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // Inicijalizacija strukture za AES kontekst
    AES_KEY aes_key;
    
    // Alokacija memorije za IV (16 bajta za AES-128)
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        return result;
    }
    
    // Generisanje nasumičnog IV
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    
    // Alokacija memorije za ključ (16 bajta za AES-128)
    result.key = (unsigned char*)malloc(16);
    if (result.key == NULL) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    
    // Kopiranje prvih 16 bajtova iz ulaznog ključa
    memcpy(result.key, key, 16);
    
    // Postavljanje ključa za enkripciju
    if (AES_set_encrypt_key(result.key, 128, &aes_key) != 0) {
        free(result.iv);
        free(result.key);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Izračunavanje veličine za enkriptovane podatke
    // Dodajemo padding za CBC mod
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.iv);
        free(result.key);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Kopiranje originalnih podataka u bafer za padding
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // Primena PKCS#7 paddinga
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Enkripcija podataka u CBC modu
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // Čišćenje bafera za padding
    free(padded_data);
    
    return result;
}