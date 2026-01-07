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
    encryption_result result;
    AES_KEY enc_key;
    unsigned char iv[AES_BLOCK_SIZE];
    
    // Initialisiere den IV mit Zufallszahlen
    if (!RAND_bytes(iv, sizeof(iv))) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Der Schlüssel für AES muss 128, 192 oder 256 Bit lang sein
    size_t key_size = (key_len >= 32) ? 32 : key_len; // maximale Länge ist 256 Bit
    unsigned char aes_key[32];
    memcpy(aes_key, key, key_size);

    // Berechne die benötigte Länge für die verschlüsselten Daten
    size_t padded_len = ((data_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Pad the data for AES
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Zero padding

    // Setzen Sie den AES Schlüssel
    AES_set_encrypt_key(aes_key, key_size * 8, &enc_key);
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &enc_key, iv, AES_ENCRYPT);

    // Setze die Rückgabewerte
    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_size);
    if (result.iv != NULL) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    if (result.key != NULL) {
        memcpy(result.key, aes_key, key_size);
    }

    // Bereinige
    free(padded_data);
    
    return result;
}