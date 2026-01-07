#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Retourenwerte-Struktur
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Verschlüsseln Sie die Daten mit dem Schlüssel unter Verwendung von AES und CBC-Modus.
Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes). Verwenden Sie das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht.
Geben Sie die verschlüsselten Daten, den IV (Initialisierungsvektor) und den für die Verschlüsselung verwendeten Schlüssel zurück.

@param key Die Bytes zur Generierung des Verschlüsselungsschlüssels.
@param data Die zu verschlüsselnden Daten.

@return Die verschlüsselten Daten, der IV und der für die Verschlüsselung verwendete Schlüssel. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Überprüfen der Eingabeparameter
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // AES-256-CBC benötigt 32-Byte-Schlüssel und 16-Byte-IV
    const int AES_KEY_LENGTH = 32; // 256 Bit
    const int AES_BLOCK_SIZE = 16; // 128 Bit
    
    // Schlüssel aus den ersten 32 Bytes des Eingabeschlüssels extrahieren
    unsigned char* aes_key = (unsigned char*)malloc(AES_KEY_LENGTH);
    if (aes_key == NULL) {
        return result;
    }
    memcpy(aes_key, key, AES_KEY_LENGTH);
    
    // IV generieren
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
    
    // Padding für die Eingabedaten berechnen
    size_t padded_len = data_len + (AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // Daten kopieren und PKCS#7 Padding anwenden
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Ausgabepuffer für verschlüsselte Daten
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (encrypted == NULL) {
        free(aes_key);
        free(iv);
        free(padded_data);
        return result;
    }
    
    // AES-Kontext initialisieren
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key, AES_KEY_LENGTH * 8, &aes_ctx) != 0) {
        free(aes_key);
        free(iv);
        free(padded_data);
        free(encrypted);
        return result;
    }
    
    // Daten verschlüsseln
    unsigned char ivec[AES_BLOCK_SIZE];
    memcpy(ivec, iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_ctx, ivec, AES_ENCRYPT);
    
    // Ergebnisstruktur füllen
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = aes_key;
    
    // Temporäre Puffer freigeben
    free(padded_data);
    
    return result;
}