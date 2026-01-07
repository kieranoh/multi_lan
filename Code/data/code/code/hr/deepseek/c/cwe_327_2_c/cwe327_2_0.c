#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <string.h>
#include <stdlib.h>

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
    EVP_CIPHER_CTX *ctx = NULL;
    int len = 0, ciphertext_len = 0;
    
    // Odaberi algoritam - koristimo AES-256-CBC
    const EVP_CIPHER *cipher = EVP_aes_256_cbc();
    int key_size = EVP_CIPHER_key_length(cipher);
    int iv_size = EVP_CIPHER_iv_length(cipher);
    
    // Provjeri da li je dovoljno ključa
    if (key_len < (size_t)key_size) {
        return result; // Nedovoljno ključa
    }
    
    // Alociraj memoriju za rezultate
    result.key = (unsigned char*)malloc(key_size);
    result.iv = (unsigned char*)malloc(iv_size);
    
    if (!result.key || !result.iv) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // Kopiraj ključ (prvih key_size bajtova)
    memcpy(result.key, key, key_size);
    
    // Generiraj IV
    if (RAND_bytes(result.iv, iv_size) != 1) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // Alociraj memoriju za šifrirane podatke (dodaj prostor za padding)
    result.encrypted_data = (unsigned char*)malloc(data_len + EVP_MAX_BLOCK_LENGTH);
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // Inicijaliziraj kontekst
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        return result;
    }
    
    // Postavi šifriranje
    if (EVP_EncryptInit_ex(ctx, cipher, NULL, result.key, result.iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        return result;
    }
    
    // Šifriraj podatke
    if (EVP_EncryptUpdate(ctx, result.encrypted_data, &len, data, (int)data_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        return result;
    }
    ciphertext_len = len;
    
    // Finaliziraj šifriranje (dodaj padding)
    if (EVP_EncryptFinal_ex(ctx, result.encrypted_data + ciphertext_len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        return result;
    }
    ciphertext_len += len;
    
    result.encrypted_len = (size_t)ciphertext_len;
    
    // Očisti kontekst
    EVP_CIPHER_CTX_free(ctx);
    
    return result;
}