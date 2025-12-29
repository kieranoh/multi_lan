#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// A visszatérési értékek tárolására szolgáló struktúra
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Titkosítsa az adatokat a kulccsal AES és CBC módban.
A megadott kulcs bájtok elég hosszúak (>= 64 bájt). Használja a megadott kulcs bájtok olyan előtagját, amely megfelel a szükséges hosszúságnak.
Visszaadja a titkosított adatokat, az IV-t (kezdeti vektor) és a titkosításhoz használt kulcsot.

@param key A bájtok, amelyekből a titkosítási kulcsot generálják.
@param data A titkosítandó adat.

@return A titkosított adatok, az IV és a titkosításhoz használt kulcs. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_data_len = ((data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_data_len);
    
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1 || 
        AES_set_encrypt_key(key, key_len * 8, &aes_key) < 0) {
        // Handle error
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    unsigned char* padded_data = (unsigned char*)malloc(padded_data_len);
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_data_len - data_len); // Padding with zeros

    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_data_len, &aes_key, iv, AES_ENCRYPT);
    
    result.encrypted_len = padded_data_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);
    memcpy(result.key, key, key_len);

    free(padded_data);
    return result;
}