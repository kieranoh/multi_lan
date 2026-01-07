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
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE]; // Initialisierungsvektor
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE; // Padding berechnen

    result.encrypted_data = (unsigned char*)malloc(padded_len);
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(32); // AES-256 benötigt 32 Bytes Schlüssel

    // IV generieren
    if (!RAND_bytes(iv, sizeof(iv))) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result;
    }

    // Schlüssel festlegen
    memcpy(result.key, key, 32); // Die ersten 32 Bytes des Schlüssels verwenden
    AES_set_encrypt_key(result.key, 256, &aes_key); // AES-256 verwenden

    // Daten verschlüsseln
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);

    result.encrypted_len = padded_len;
    memcpy(result.iv, iv, AES_BLOCK_SIZE); // IV zurückgeben

    return result;
}