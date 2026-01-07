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
    
    // Ellenőrizzük az alapvető paramétereket
    if (key == NULL || data == NULL || key_len < 16) {
        return result;
    }
    
    // AES-256 CBC-hez 32 bájtos kulcs és 16 bájtos IV szükséges
    const int AES_KEY_SIZE = 32; // 256 bites
    const int AES_IV_SIZE = 16;  // 128 bites
    
    // Foglaljunk memóriát a kulcshoz (32 bájt AES-256-hoz)
    result.key = (unsigned char*)malloc(AES_KEY_SIZE);
    if (result.key == NULL) {
        return result;
    }
    
    // Használjuk a megadott kulcs első 32 bájtját
    size_t copy_len = (key_len < AES_KEY_SIZE) ? key_len : AES_KEY_SIZE;
    memcpy(result.key, key, copy_len);
    
    // Ha a kulcs rövidebb, töltjük fel nullákkal
    if (copy_len < AES_KEY_SIZE) {
        memset(result.key + copy_len, 0, AES_KEY_SIZE - copy_len);
    }
    
    // Foglaljunk memóriát az IV-hez
    result.iv = (unsigned char*)malloc(AES_IV_SIZE);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Generáljunk véletlen IV-t
    if (RAND_bytes(result.iv, AES_IV_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Számítsuk ki a titkosított adatok méretét
    // AES CBC-ben padding van, így a méret többszöröse a blokkméretnek (16 bájt)
    size_t padded_len = ((data_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Inicializáljuk az AES kontextust
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, AES_KEY_SIZE * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Titkosítás AES CBC módban
    // Mivel a forrásadatok nem feltétlenül többszörösei a blokkméretnek,
    // először másoljuk és padoljuk az adatokat
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
    
    // Másoljuk az eredeti adatokat
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 padding hozzáadása
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    memset(padded_data + data_len, pad_value, pad_value);
    
    // Titkosítás
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // Tisztítás
    free(padded_data);
    
    return result;
}