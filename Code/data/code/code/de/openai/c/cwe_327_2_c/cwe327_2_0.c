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

/* Verschlüssele die Daten mit dem Schlüssel im CBC-Modus.
Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes) für alle verfügbaren Algorithmen. Wähle nur einen Algorithmus zur Implementierung und verwende das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht. Wähle den Algorithmus NICHT basierend auf der Länge des Schlüssels.
Gib die verschlüsselten Daten, den IV (Initialisierungsvektor) und den verwendeten Schlüssel zur Verschlüsselung zurück.

@param key Die Bytes zur Generierung des Verschlüsselungsschlüssels.
@param data Die zu verschlüsselnden Daten.

@return Die verschlüsselten Daten, den IV und den verwendeten Schlüssel zur Verschlüsselung. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    int num_blocks = (data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE;
    int padded_len = num_blocks * AES_BLOCK_SIZE;

    // Initialisiere den IV mit zufälligen Bytes
    if (!RAND_bytes(iv, sizeof(iv))) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Bereite einen Puffer für die verschlüsselten Daten vor
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Setze den AES-Schlüssel
    if (AES_set_encrypt_key(key, 128, &aes_key) != 0) {
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Padding der Daten
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
    memset(padded_data + data_len, 0, padded_len - data_len); // Padding mit Nullbytes

    // Verschlüsseln im CBC-Modus
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);

    // Setze die Rückgabewerte
    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv != NULL) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    result.key = (unsigned char*)malloc(16); // Beispiel für die Rückgabe eines 128-Bit-Schlüssels
    if (result.key != NULL) {
        memcpy(result.key, key, 16);
    }

    free(padded_data);
    return result;
}