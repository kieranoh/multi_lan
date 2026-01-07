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
    const int AES_KEY_LENGTH = 32;
    
    // IV für CBC-Modus: 16 Bytes für AES
    const int IV_LENGTH = 16;
    
    // Berechnen der benötigten Pufferlänge für verschlüsselte Daten
    // PKCS#7 Padding: Fügt bis zu AES_BLOCK_SIZE Bytes hinzu
    size_t padded_len = data_len + AES_BLOCK_SIZE;
    
    // Speicher für verschlüsselte Daten allokieren
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (encrypted == NULL) {
        return result;
    }
    
    // Speicher für IV allokieren
    unsigned char* iv = (unsigned char*)malloc(IV_LENGTH);
    if (iv == NULL) {
        free(encrypted);
        return result;
    }
    
    // Speicher für den tatsächlichen Schlüssel allokieren
    unsigned char* actual_key = (unsigned char*)malloc(AES_KEY_LENGTH);
    if (actual_key == NULL) {
        free(encrypted);
        free(iv);
        return result;
    }
    
    // Ersten 32 Bytes der bereitgestellten Schlüsselbytes als AES-256 Schlüssel verwenden
    memcpy(actual_key, key, AES_KEY_LENGTH);
    
    // Zufälligen IV generieren
    if (RAND_bytes(iv, IV_LENGTH) != 1) {
        free(encrypted);
        free(iv);
        free(actual_key);
        return result;
    }
    
    // AES-Kontext initialisieren
    AES_KEY aes_key;
    if (AES_set_encrypt_key(actual_key, 256, &aes_key) != 0) {
        free(encrypted);
        free(iv);
        free(actual_key);
        return result;
    }
    
    // Daten für Verschlüsselung vorbereiten (Kopie mit Padding)
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(encrypted);
        free(iv);
        free(actual_key);
        return result;
    }
    
    // Originaldaten kopieren
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 Padding hinzufügen
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = 0; i < padding; i++) {
        padded_data[data_len + i] = (unsigned char)padding;
    }
    
    // Verschlüsseln mit AES-CBC
    AES_cbc_encrypt(padded_data, encrypted, data_len + padding, &aes_key, iv, AES_ENCRYPT);
    
    // Ergebnisstruktur füllen
    result.encrypted_data = encrypted;
    result.encrypted_len = data_len + padding;
    result.iv = iv;
    result.key = actual_key;
    
    // Temporären Puffer freigeben
    free(padded_data);
    
    return result;
}