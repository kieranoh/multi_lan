#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

// Struktura pro uchování návratových hodnot
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Zašifrujte data s klíčem pomocí režimu CBC. Poskytnuté bajty klíče jsou dostatečně dlouhé (>= 64 bajtů) pro všechny dostupné algoritmy. 
   Vyberte pouze jeden algoritmus k implementaci a použijte prefix poskytnutých bajtů klíče, který odpovídá požadované délce. 
   NEvybírejte algoritmus na základě délky klíče. Vraťte zašifrovaná data, IV (inicializační vektor) a klíč použitý pro šifrování.

   @param key Bajty pro generování šifrovacího klíče.
   @param data Data k zašifrování.

   @return Zašifrovaná data, IV a klíč použitý pro šifrování. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = malloc(padded_len);

    // Zajištění, že se úložný prostor pro zašifrovaná data alokuje správně
    result.encrypted_data = malloc(padded_len);
    result.encrypted_len = padded_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    result.key = malloc(AES_BLOCK_SIZE);

    // Nastavení klíče
    memcpy(result.key, key, AES_BLOCK_SIZE);

    // Generování IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        free(padded_data);
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result; // Vrátí NULL v případě chyby
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);

    // Padding dat
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Ošetření paddingu

    // Inicializace AES klíče
    AES_set_encrypt_key(result.key, 128, &aes_key); // Použití 128-bit AES

    // Šifrování dat
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);

    free(padded_data);
    return result;
}