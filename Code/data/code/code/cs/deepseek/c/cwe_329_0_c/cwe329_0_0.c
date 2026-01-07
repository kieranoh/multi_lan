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
    
    // Kontrola vstupních parametrů
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // Vytvoření AES klíče (256-bit = 32 bajtů)
    const int AES_KEY_LENGTH = 32;
    unsigned char* aes_key = (unsigned char*)malloc(AES_KEY_LENGTH);
    if (aes_key == NULL) {
        return result;
    }
    
    // Použijeme prvních 32 bajtů z poskytnutého klíče
    memcpy(aes_key, key, AES_KEY_LENGTH);
    
    // Alokace a generování IV (16 bajtů pro AES CBC)
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (iv == NULL) {
        free(aes_key);
        return result;
    }
    
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // Výpočet délky zašifrovaných dat (zarovnání na blok)
    size_t padded_len = data_len;
    if (data_len % AES_BLOCK_SIZE != 0) {
        padded_len = ((data_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    }
    
    // Alokace paměti pro zašifrovaná data
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (encrypted == NULL) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // Příprava dat pro šifrování (kopie vstupních dat)
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(aes_key);
        free(iv);
        free(encrypted);
        return result;
    }
    
    // Kopírování dat a doplnění nulami (PKCS#7 padding by byl lepší, ale pro jednoduchost použijeme zero padding)
    memcpy(padded_data, data, data_len);
    if (padded_len > data_len) {
        memset(padded_data + data_len, 0, padded_len - data_len);
    }
    
    // Inicializace AES kontextu
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key, AES_KEY_LENGTH * 8, &aes_ctx) != 0) {
        free(aes_key);
        free(iv);
        free(encrypted);
        free(padded_data);
        return result;
    }
    
    // Šifrování v režimu CBC
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_ctx, iv, AES_ENCRYPT);
    
    // Ukládání výsledků
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = aes_key;
    
    // Uvolnění dočasných dat
    free(padded_data);
    
    return result;
}