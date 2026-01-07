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

    // Verifica che la lunghezza della chiave sia sufficiente
    if (key_len < AES_BLOCK_SIZE) {
        return result; // Restituisce risultati vuoti in caso di errore
    }

    // Inizializzazione della chiave AES e IV
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];

    // Genera un IV casuale
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        return result; // Restituisce risultati vuoti in caso di errore
    }

    // Imposta la chiave AES
    if (AES_set_encrypt_key(key, key_len * 8, &aes_key) < 0) {
        return result; // Restituisce risultati vuoti in caso di errore
    }

    // Calcola la lunghezza dei dati crittografati
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        return result; // Restituisce risultati vuoti in caso di errore
    }

    // Crittografa i dati
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, iv, AES_ENCRYPT);

    // Imposta i risultati
    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv != NULL) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    result.key = (unsigned char*)malloc(key_len);
    if (result.key != NULL) {
        memcpy(result.key, key, key_len);
    }

    return result;
}