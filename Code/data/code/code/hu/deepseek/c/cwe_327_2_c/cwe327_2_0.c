#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

// A visszatérési értékeket tároló struktúra
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Titkosítsa az adatokat a kulccsal CBC módban.
A megadott kulcs bájtok elég hosszúak (>= 64 bájt) az összes elérhető algoritmushoz. Csak egy algoritmust válasszon ki a megvalósításhoz, és használja a megadott kulcs bájtoknak azt a prefixét, amely megfelel a szükséges hosszúságnak. NE válassza az algoritmust a kulcs hossza alapján.
Adja vissza a titkosított adatokat, az IV-t (kezdeményezési vektor), és a titkosításhoz használt kulcsot.

@param key A bájtok, amelyekből a titkosítási kulcsot generálják.
@param data A titkosítandó adat.

@return A titkosított adatokat, az IV-t, és a titkosításhoz használt kulcsot. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Válasszuk az AES-256 CBC algoritmust (fix választás)
    const int algorithm = 1; // 1 = AES-256 CBC
    
    if (algorithm == 1) { // AES-256 CBC
        // AES-256 CBC-hez szükséges kulcs hossz: 32 bájt (256 bit)
        const size_t aes_key_len = 32;
        // IV hossz AES CBC-hez: 16 bájt (128 bit)
        const size_t iv_len = 16;
        
        // Ellenőrizzük, hogy van-e elég kulcs adat
        if (key_len < aes_key_len) {
            return result; // Nem elég hosszú a kulcs
        }
        
        // Foglaljunk memóriát az eredményeknek
        result.key = (unsigned char*)malloc(aes_key_len);
        result.iv = (unsigned char*)malloc(iv_len);
        
        if (!result.key || !result.iv) {
            free(result.key);
            free(result.iv);
            return result;
        }
        
        // Másoljuk a kulcs első 32 bájtját
        memcpy(result.key, key, aes_key_len);
        
        // Generáljunk random IV-t
        if (RAND_bytes(result.iv, iv_len) != 1) {
            free(result.key);
            free(result.iv);
            return result;
        }
        
        // AES CBC titkosítás előkészítése
        AES_KEY aes_key;
        if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
            free(result.key);
            free(result.iv);
            return result;
        }
        
        // CBC módban a titkosított adat hossza padding miatt lehet több
        // AES blokk méret: 16 bájt
        const size_t block_size = 16;
        size_t padded_len = ((data_len + block_size - 1) / block_size) * block_size;
        result.encrypted_data = (unsigned char*)malloc(padded_len);
        
        if (!result.encrypted_data) {
            free(result.key);
            free(result.iv);
            return result;
        }
        
        // Másoljuk az adatokat a bufferbe (padding hozzáadásához)
        unsigned char* padded_data = (unsigned char*)malloc(padded_len);
        if (!padded_data) {
            free(result.key);
            free(result.iv);
            free(result.encrypted_data);
            result.encrypted_data = NULL;
            return result;
        }
        
        memcpy(padded_data, data, data_len);
        
        // PKCS#7 padding hozzáadása
        unsigned char pad_value = block_size - (data_len % block_size);
        for (size_t i = data_len; i < padded_len; i++) {
            padded_data[i] = pad_value;
        }
        
        // Titkosítás CBC módban
        unsigned char ivec[iv_len];
        memcpy(ivec, result.iv, iv_len);
        
        AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                       &aes_key, ivec, AES_ENCRYPT);
        
        result.encrypted_len = padded_len;
        free(padded_data);
    }
    
    return result;
}