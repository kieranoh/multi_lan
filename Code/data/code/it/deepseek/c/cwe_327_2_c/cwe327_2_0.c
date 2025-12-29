#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <string.h>
#include <stdlib.h>

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
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Verifica parametri di input
    if (key == NULL || data == NULL || key_len < 16) {
        return result;
    }
    
    // Scelgo AES-256-CBC come algoritmo (scelta fissa, non basata sulla lunghezza della chiave)
    const EVP_CIPHER* cipher = EVP_aes_256_cbc();
    int key_size = EVP_CIPHER_key_length(cipher);  // 32 byte per AES-256
    int iv_size = EVP_CIPHER_iv_length(cipher);    // 16 byte per AES CBC
    
    // Alloca memoria per la chiave utilizzata
    result.key = (unsigned char*)malloc(key_size);
    if (result.key == NULL) {
        return result;
    }
    
    // Copia i primi key_size byte dalla chiave fornita
    memcpy(result.key, key, key_size);
    
    // Alloca memoria per l'IV
    result.iv = (unsigned char*)malloc(iv_size);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Genera IV casuale
    if (RAND_bytes(result.iv, iv_size) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Crea e inizializza il contesto di cifratura
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Inizializza l'operazione di cifratura
    if (EVP_EncryptInit_ex(ctx, cipher, NULL, result.key, result.iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Alloca memoria per i dati cifrati (dati + padding)
    // Per CBC, il padding può aggiungere fino a un blocco intero
    size_t max_encrypted_len = data_len + EVP_CIPHER_block_size(cipher);
    result.encrypted_data = (unsigned char*)malloc(max_encrypted_len);
    if (result.encrypted_data == NULL) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    int out_len = 0;
    int final_len = 0;
    
    // Cifra i dati
    if (EVP_EncryptUpdate(ctx, result.encrypted_data, &out_len, data, data_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.encrypted_data);
        free(result.key);
        free(result.iv);
        result.encrypted_data = NULL;
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Finalizza la cifratura (aggiunge il padding)
    if (EVP_EncryptFinal_ex(ctx, result.encrypted_data + out_len, &final_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.encrypted_data);
        free(result.key);
        free(result.iv);
        result.encrypted_data = NULL;
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    result.encrypted_len = out_len + final_len;
    
    // Pulisci il contesto
    EVP_CIPHER_CTX_free(ctx);
    
    return result;
}