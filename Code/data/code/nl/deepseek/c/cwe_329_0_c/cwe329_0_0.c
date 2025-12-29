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
    
    // Controleer of de sleutel lang genoeg is (minimaal 32 bytes voor AES-256)
    if (key_len < 32) {
        return result; // Sleutel is te kort
    }
    
    // Maak een kopie van de eerste 32 bytes van de sleutel voor AES-256
    unsigned char* aes_key = (unsigned char*)malloc(32);
    if (!aes_key) {
        return result;
    }
    memcpy(aes_key, key, 32);
    
    // Genereer een willekeurige IV van 16 bytes (AES blokgrootte)
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!iv) {
        free(aes_key);
        return result;
    }
    
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // Bereken de benodigde grootte voor versleutelde gegevens
    // AES CBC voegt padding toe om een veelvoud van blokgrootte te bereiken
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (!encrypted) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // Stel de encryptie context in
    AES_KEY aes_key_struct;
    if (AES_set_encrypt_key(aes_key, 256, &aes_key_struct) != 0) {
        free(aes_key);
        free(iv);
        free(encrypted);
        return result;
    }
    
    // Versleutel de gegevens met AES CBC modus
    // We gebruiken een lokale buffer voor padding omdat AES_cbc_encrypt de invoer wijzigt
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(aes_key);
        free(iv);
        free(encrypted);
        return result;
    }
    
    // Kopieer de originele gegevens en voeg PKCS#7 padding toe
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 padding
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Voer de versleuteling uit
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_key_struct, iv, AES_ENCRYPT);
    
    free(padded_data);
    
    // Vul het resultaat in
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = aes_key;
    
    return result;
}