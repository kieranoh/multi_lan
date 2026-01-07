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
    
    // IV für CBC-Modus: 16 Bytes für AES
    const size_t iv_len = 16;
    
    // Allokieren und kopieren des Schlüssels (nur die ersten 32 Bytes verwenden)
    result.key = (unsigned char*)malloc(aes_key_len);
    if (result.key == NULL) {
        return result;
    }
    memcpy(result.key, key, aes_key_len);
    
    // Allokieren und generieren des IV
    result.iv = (unsigned char*)malloc(iv_len);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Zufälligen IV generieren
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Padding für die Eingabedaten berechnen
    // PKCS#7 Padding: Füge n Bytes mit Wert n hinzu, wobei n die Anzahl der Padding-Bytes ist
    size_t padding_len = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    if (padding_len == 0) {
        padding_len = AES_BLOCK_SIZE; // Ein ganzer Block Padding, wenn Daten bereits blockausgerichtet sind
    }
    
    size_t padded_data_len = data_len + padding_len;
    
    // Allokieren und kopieren der Daten mit Padding
    unsigned char* padded_data = (unsigned char*)malloc(padded_data_len);
    if (padded_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Originaldaten kopieren
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 Padding hinzufügen
    for (size_t i = 0; i < padding_len; i++) {
        padded_data[data_len + i] = (unsigned char)padding_len;
    }
    
    // Allokieren für verschlüsselte Daten
    result.encrypted_data = (unsigned char*)malloc(padded_data_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        free(padded_data);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // AES-Kontext initialisieren
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(padded_data);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Verschlüsselung mit CBC-Modus durchführen
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_data_len, &aes_key, result.iv, AES_ENCRYPT);
    
    // Länge der verschlüsselten Daten setzen
    result.encrypted_len = padded_data_len;
    
    // Temporären Puffer freigeben
    free(padded_data);
    
    return result;
}