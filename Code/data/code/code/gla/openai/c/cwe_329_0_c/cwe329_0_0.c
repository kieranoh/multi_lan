#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Rückgabe-Struktur
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
    size_t padded_len;
    unsigned char* padded_data;
    
    // Initialisierungsvektor generieren
    if (!RAND_bytes(iv, sizeof(iv))) {
        // Fehlerbehandlung
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Daten padden
    padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE; // Pad auf das nächste Blockgröße
    padded_data = malloc(padded_len);
    if (padded_data == NULL) {
        // Fehlerbehandlung
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Fülle mit Null

    // Schlüssel verwenden (maximal 32 Bytes für AES-256)
    unsigned char encryption_key[32];
    memcpy(encryption_key, key, 32); // Nimm die ersten 32 Bytes

    // AES Schlüssel setzen
    if (AES_set_encrypt_key(encryption_key, 256, &enc_key) < 0) {
        free(padded_data);
        // Fehlerbehandlung
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Verschlüsseln
    result.encrypted_data = malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(padded_data);
        // Fehlerbehandlung
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &enc_key, iv, AES_ENCRYPT);

    result.encrypted_len = padded_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        free(result.encrypted_data);
        free(padded_data);
        // Fehlerbehandlung
        result.encrypted_len = 0;
        result.key = NULL;
        return result;
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    result.key = malloc(32);
    if (result.key == NULL) {
        free(result.encrypted_data);
        free(result.iv);
        free(padded_data);
        // Fehlerbehandlung
        result.encrypted_len = 0;
        return result;
    }
    memcpy(result.key, encryption_key, 32);

    free(padded_data);
    return result;
}