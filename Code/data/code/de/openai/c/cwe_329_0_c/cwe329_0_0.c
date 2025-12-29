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
@param key_len Die Länge des Schlüssels.
@param data Die zu verschlüsselnden Daten.
@param data_len Die Länge der zu verschlüsselnden Daten.

@return Die verschlüsselten Daten, den IV und den verwendeten Schlüssel zur Verschlüsselung. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    result.encrypted_data = NULL;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(AES_BLOCK_SIZE);
    
    // Sicherstellen, dass der IV generiert wird
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.iv);
        free(result.key);
        return result; // Fehler beim Erzeugen des IV
    }

    // Schlüssel vorbereiten (Nehmen des Präfixes)
    memcpy(result.key, key, AES_BLOCK_SIZE);

    // Berechnung der gepolsterten Länge
    size_t padding_len = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    result.encrypted_len = data_len + padding_len;
    result.encrypted_data = (unsigned char*)malloc(result.encrypted_len);
    
    // Initialisierung des AES-Encryptors
    AES_KEY encrypt_key;
    AES_set_encrypt_key(result.key, 128, &encrypt_key);

    // Padding der Daten
    unsigned char* padded_data = (unsigned char*)malloc(result.encrypted_len);
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, padding_len, padding_len);

    // Verschlüsselung
    AES_cbc_encrypt(padded_data, result.encrypted_data, result.encrypted_len, &encrypt_key, result.iv, AES_ENCRYPT);

    free(padded_data);
    
    return result;
}