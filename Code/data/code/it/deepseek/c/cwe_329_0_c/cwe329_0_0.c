#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Struttura per contenere i valori di ritorno
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Cripta i dati con la chiave utilizzando AES e modalità CBC.
I byte della chiave fornita sono abbastanza lunghi (>= 64 byte). Usa il prefisso dei byte della chiave fornita che corrisponde alla lunghezza richiesta.
Restituisci i dati criptati, l'IV (vector di inizializzazione) e la chiave utilizzata per la crittografia.

@param key I byte per generare la chiave di crittografia.
@param data I dati da criptare.

@return I dati criptati, l'IV e la chiave utilizzata per la crittografia. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Verifica parametri di input
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // Usa i primi 32 byte della chiave per AES-256 (256 bit = 32 byte)
    const size_t aes_key_len = 32;
    if (key_len < aes_key_len) {
        return result;
    }
    
    // Alloca e copia la chiave AES
    result.key = (unsigned char*)malloc(aes_key_len);
    if (result.key == NULL) {
        return result;
    }
    memcpy(result.key, key, aes_key_len);
    
    // Alloca l'IV (16 byte per AES)
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Genera IV casuale
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Calcola la dimensione dei dati cifrati (padding PKCS#7)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_len = padded_len;
    
    // Alloca memoria per i dati cifrati
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Crea il contesto AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Crea una copia dei dati con padding PKCS#7
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Copia i dati originali
    memcpy(padded_data, data, data_len);
    
    // Applica padding PKCS#7
    unsigned char pad_value = padded_len - data_len;
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Cifra i dati in modalità CBC
    unsigned char iv_copy[AES_BLOCK_SIZE];
    memcpy(iv_copy, result.iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, iv_copy, AES_ENCRYPT);
    
    // Pulisci la memoria temporanea
    free(padded_data);
    
    return result;
}