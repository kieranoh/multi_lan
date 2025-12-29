#include <openssl/aes.h>
#include <openssl/des.h>
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
    
    // Val av algoritm: AES-256-CBC (fast algoritm, inte baserat på nyckellängd)
    const int algorithm = 1; // 1 för AES-256-CBC
    
    if (algorithm == 1) { // AES-256-CBC
        // Kontrollera att nyckeln är tillräckligt lång (minst 32 bytes för AES-256)
        if (key_len < 32) {
            // Returnera tomt resultat om nyckeln är för kort
            return result;
        }
        
        // Allokera minne för IV (16 bytes för AES CBC)
        result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
        if (!result.iv) {
            return result;
        }
        
        // Generera slumpmässig IV
        if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
            free(result.iv);
            result.iv = NULL;
            return result;
        }
        
        // Allokera minne för nyckeln (32 bytes för AES-256)
        result.key = (unsigned char*)malloc(32);
        if (!result.key) {
            free(result.iv);
            result.iv = NULL;
            return result;
        }
        
        // Kopiera de första 32 byten från input-nyckeln
        memcpy(result.key, key, 32);
        
        // Beräkna utdata-storlek (padderad till AES_BLOCK_SIZE)
        size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
        
        // Allokera minne för krypterad data
        result.encrypted_data = (unsigned char*)malloc(padded_len);
        if (!result.encrypted_data) {
            free(result.iv);
            free(result.key);
            result.iv = NULL;
            result.key = NULL;
            return result;
        }
        
        // Skapa AES-nyckelstruktur
        AES_KEY aes_key;
        if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
            free(result.encrypted_data);
            free(result.iv);
            free(result.key);
            result.encrypted_data = NULL;
            result.iv = NULL;
            result.key = NULL;
            return result;
        }
        
        // Skapa kopia av data för padding
        unsigned char* padded_data = (unsigned char*)malloc(padded_len);
        if (!padded_data) {
            free(result.encrypted_data);
            free(result.iv);
            free(result.key);
            result.encrypted_data = NULL;
            result.iv = NULL;
            result.key = NULL;
            return result;
        }
        
        // Kopiera originaldata och lägg till PKCS7-padding
        memcpy(padded_data, data, data_len);
        unsigned char pad_value = padded_len - data_len;
        for (size_t i = data_len; i < padded_len; i++) {
            padded_data[i] = pad_value;
        }
        
        // Utför AES-CBC-kryptering
        AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                       &aes_key, result.iv, AES_ENCRYPT);
        
        result.encrypted_len = padded_len;
        
        // Rensa och frigör temporär data
        free(padded_data);
        
        return result;
    }
    
    // Returnera tomt resultat om ingen algoritm valdes
    return result;
}