#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// A visszatérési értékeket tároló struktúra
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Titkosítsa az adatokat a kulccal CBC módban.
A megadott kulcs bájtok elég hosszúak (>= 64 bájt) az összes elérhető algoritmushoz. Csak egy algoritmust válasszon ki a megvalósításhoz, és használja a megadott kulcs bájtoknak azt a prefixét, amely megfelel a szükséges hosszúságnak. NE válassza az algoritmust a kulcs hossza alapján.
Adja vissza a titkosított adatokat, az IV-t (kezdeményezési vektor), és a titkosításhoz használt kulcsot.

@param key A bájtok, amelyekből a titkosítási kulcsot generálják.
@param data A titkosítandó adat.

@return A titkosított adatokat, az IV-t, és a titkosításhoz használt kulcsot. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(AES_BLOCK_SIZE);
    
    // Generálj egy véletlenszerű inicializáló vektort
    if (!RAND_bytes(result.iv, AES_BLOCK_SIZE)) {
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }

    // Használja az AES algoritmust 128 bites kulccsal (első 16 byte)
    AES_KEY aes_key;
    size_t aes_key_len = 16; // 128 bits
    memcpy(result.key, key, aes_key_len);
    
    size_t padded_len = data_len + (AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Padded with zeros

    AES_set_encrypt_key(result.key, 128, &aes_key);
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);

    result.encrypted_len = padded_len;

    free(padded_data);
    return result;
}