#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Vybereme AES-256-CBC jako algoritmus (pevná volba podle specifikace)
    const int algorithm = 1; // 1 = AES-256-CBC
    
    // Kontrola vstupních parametrů
    if (key == NULL || data == NULL || key_len < 32) {
        return result;
    }
    
    // Inicializace výsledkové struktury
    result.iv = NULL;
    result.key = NULL;
    result.encrypted_data = NULL;
    result.encrypted_len = 0;
    
    // Vygenerování IV (inicializační vektor)
    unsigned char iv[AES_BLOCK_SIZE];
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        return result;
    }
    
    // Alokace paměti pro IV v návratové struktuře
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        return result;
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    
    // Příprava klíče pro AES-256 (prvních 32 bajtů z poskytnutého klíče)
    unsigned char aes_key[32];
    memcpy(aes_key, key, 32);
    
    // Alokace paměti pro klíč v návratové struktuře
    result.key = (unsigned char*)malloc(32);
    if (result.key == NULL) {
        free(result.iv);
        return result;
    }
    memcpy(result.key, aes_key, 32);
    
    // Výpočet délky zašifrovaných dat (zarovnání na blok AES)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // Alokace paměti pro zašifrovaná data
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.iv);
        free(result.key);
        return result;
    }
    
    // Příprava dat pro šifrování (kopie vstupních dat)
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.iv);
        free(result.key);
        free(result.encrypted_data);
        return result;
    }
    
    // Kopie dat a doplnění PKCS7 paddingem
    memcpy(padded_data, data, data_len);
    
    // PKCS7 padding
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Inicializace AES kontextu
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key, 256, &aes_ctx) != 0) {
        free(result.iv);
        free(result.key);
        free(result.encrypted_data);
        free(padded_data);
        return result;
    }
    
    // Šifrování v režimu CBC
    unsigned char ivec[AES_BLOCK_SIZE];
    memcpy(ivec, iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_ctx, ivec, AES_ENCRYPT);
    
    // Uložení délky zašifrovaných dat
    result.encrypted_len = padded_len;
    
    // Vyčištění dočasných dat
    free(padded_data);
    
    return result;
}