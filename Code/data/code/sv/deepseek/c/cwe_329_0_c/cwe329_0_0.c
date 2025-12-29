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
    
    // Kontrollera indata
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // AES-256 kräver 32 byte nyckel
    const size_t AES_KEY_LENGTH = 32;
    
    // Allokera minne för nyckeln
    result.key = (unsigned char*)malloc(AES_KEY_LENGTH);
    if (result.key == NULL) {
        return result;
    }
    
    // Kopiera de första 32 byten från den angivna nyckeln
    memcpy(result.key, key, AES_KEY_LENGTH);
    
    // Allokera minne för IV (16 byte för AES CBC)
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Generera slumpmässig IV
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Beräkna storleken för krypterad data
    // CBC kräver padding till nästa AES_BLOCK_SIZE
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Initiera AES-kontext
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, AES_KEY_LENGTH * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Kopiera datan till en buffer för padding
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
    
    // Kopiera originaldata och lägg till PKCS#7 padding
    memcpy(padded_data, data, data_len);
    
    // Beräkna padding-byte
    unsigned char pad_byte = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    
    // Fyll med padding
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_byte;
    }
    
    // Utför AES CBC-kryptering
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    
    // Ställ in längden för krypterad data
    result.encrypted_len = padded_len;
    
    // Rensa den paddade datan
    free(padded_data);
    
    return result;
}