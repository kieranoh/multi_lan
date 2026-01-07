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
    
    // Überprüfen der Eingabeparameter
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // AES-256 benötigt 32 Bytes (256 Bits) Schlüssel
    const size_t aes_key_len = 32;
    
    // IV für CBC-Modus (16 Bytes für AES)
    const size_t iv_len = 16;
    
    // Speicher für IV allokieren
    result.iv = (unsigned char*)malloc(iv_len);
    if (result.iv == NULL) {
        return result;
    }
    
    // Zufälligen IV generieren
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    
    // Schlüssel allokieren und kopieren (nur die ersten 32 Bytes)
    result.key = (unsigned char*)malloc(aes_key_len);
    if (result.key == NULL) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    memcpy(result.key, key, aes_key_len);
    
    // Padding für die Eingabedaten berechnen
    // AES block size ist 16 Bytes
    const size_t block_size = 16;
    size_t padded_len = data_len;
    if (data_len % block_size != 0) {
        padded_len = ((data_len / block_size) + 1) * block_size;
    }
    
    // Speicher für gepaddete Daten allokieren
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.iv);
        free(result.key);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Daten kopieren und PKCS7 Padding anwenden
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = (unsigned char)(padded_len - data_len);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Speicher für verschlüsselte Daten allokieren
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.iv);
        free(result.key);
        free(padded_data);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // AES-Kontext initialisieren
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(result.iv);
        free(result.key);
        free(padded_data);
        free(result.encrypted_data);
        result.iv = NULL;
        result.key = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Daten im CBC-Modus verschlüsseln
    unsigned char iv_copy[iv_len];
    memcpy(iv_copy, result.iv, iv_len);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                    &aes_key, iv_copy, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // Gepaddete Daten freigeben
    free(padded_data);
    
    return result;
}