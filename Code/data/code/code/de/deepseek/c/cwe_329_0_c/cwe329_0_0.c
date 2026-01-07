#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Struktur zur Speicherung der Rückgabewerte
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Verschlüssele die Daten mit dem Schlüssel unter Verwendung von AES und CBC-Modus.
Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes). Verwende das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht.
Gib die verschlüsselten Daten, den IV (Initialisierungsvektor) und den verwendeten Schlüssel zur Verschlüsselung zurück.

@param key Die Bytes zur Generierung des Verschlüsselungsschlüssels.
@param data Die zu verschlüsselnden Daten.

@return Die verschlüsselten Daten, den IV und den verwendeten Schlüssel zur Verschlüsselung. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Überprüfe, ob die Eingabedaten gültig sind
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // AES-256-CBC benötigt einen 256-Bit (32 Byte) Schlüssel
    const size_t AES_KEY_SIZE = 32;
    
    // IV für CBC-Modus (16 Bytes für AES)
    const size_t IV_SIZE = 16;
    
    // Berechne die benötigte Pufferlänge für die Verschlüsselung
    // PKCS#7 Padding: Datenlänge wird auf das nächste Vielfache von 16 aufgefüllt
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // Allokiere Speicher für die verschlüsselten Daten
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        return result;
    }
    
    // Allokiere Speicher für den IV
    result.iv = (unsigned char*)malloc(IV_SIZE);
    if (result.iv == NULL) {
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }
    
    // Allokiere Speicher für den verwendeten Schlüssel
    result.key = (unsigned char*)malloc(AES_KEY_SIZE);
    if (result.key == NULL) {
        free(result.encrypted_data);
        free(result.iv);
        result.encrypted_data = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Kopiere die ersten 32 Bytes des bereitgestellten Schlüssels als AES-256-Schlüssel
    memcpy(result.key, key, AES_KEY_SIZE);
    
    // Generiere einen zufälligen IV
    if (RAND_bytes(result.iv, IV_SIZE) != 1) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Erstelle einen temporären Puffer für die gepaddeten Daten
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
    
    // Kopiere die Originaldaten und füge PKCS#7 Padding hinzu
    memcpy(padded_data, data, data_len);
    
    // Berechne den Padding-Wert
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    
    // Fülle den Rest des Puffers mit dem Padding-Wert
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Initialisiere den AES-Kontext
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        free(padded_data);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Führe die CBC-Verschlüsselung durch
    unsigned char iv_copy[IV_SIZE];
    memcpy(iv_copy, result.iv, IV_SIZE);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, iv_copy, AES_ENCRYPT);
    
    // Setze die Länge der verschlüsselten Daten
    result.encrypted_len = padded_len;
    
    // Bereinige temporären Puffer
    free(padded_data);
    
    return result;
}