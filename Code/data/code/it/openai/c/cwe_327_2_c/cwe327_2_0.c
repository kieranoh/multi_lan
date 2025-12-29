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

/* Cripta i dati con la chiave utilizzando la modalità CBC. I byte della chiave fornita sono abbastanza lunghi (>= 64 byte) per tutti gli algoritmi disponibili. Scegli solo un algoritmo da implementare e utilizza il prefisso dei byte della chiave fornita che corrisponde alla lunghezza richiesta. NON scegliere l'algoritmo in base alla lunghezza della chiave. Restituisci i dati criptati, l'IV (vector di inizializzazione) e la chiave utilizzata per la crittografia.

@param key I byte per generare la chiave di crittografia.
@param data I dati da criptare.

@return I dati criptati, l'IV e la chiave utilizzata per la crittografia. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    int num_blocks = (data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE;
    size_t padded_len = num_blocks * AES_BLOCK_SIZE;

    result.encrypted_data = (unsigned char*)malloc(padded_len);
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(AES_BLOCK_SIZE);
    memcpy(result.key, key, AES_BLOCK_SIZE);
    
    // Genera un IV casuale
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result;
    }

    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Padding con zeri

    AES_set_encrypt_key(result.key, 128, &aes_key); // Utilizzare AES a 128 bit
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);

    result.encrypted_len = padded_len;

    free(padded_data); // Libera il buffer di dati riempito
    return result;
}