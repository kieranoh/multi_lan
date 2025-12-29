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
    encryption_result result;
    result.encrypted_data = NULL;
    result.encrypted_len = 0;
    result.iv = NULL;
    result.key = NULL;
    
    // Koristimo AES-256-CBC algoritam (fiksno odabran)
    const EVP_CIPHER* cipher = EVP_aes_256_cbc();
    int iv_len = EVP_CIPHER_iv_length(cipher);
    int key_len_needed = EVP_CIPHER_key_length(cipher);
    
    // Provera da li imamo dovoljno bajtova u datom ključu
    if (key_len < (size_t)key_len_needed) {
        // Nema dovoljno bajtova za ključ
        return result;
    }
    
    // Alociraj i kopiraj ključ (uzimamo prvih key_len_needed bajtova)
    result.key = (unsigned char*)malloc(key_len_needed);
    if (!result.key) {
        return result;
    }
    memcpy(result.key, key, key_len_needed);
    
    // Alociraj i generiši IV
    result.iv = (unsigned char*)malloc(iv_len);
    if (!result.iv) {
        free(result.key);
        return result;
    }
    
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // Priprema za enkripciju
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // Inicijalizacija enkripcije
    if (EVP_EncryptInit_ex(ctx, cipher, NULL, result.key, result.iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // Alociraj bafer za enkriptovane podatke (dodaj prostor za padding)
    result.encrypted_data = (unsigned char*)malloc(data_len + EVP_CIPHER_block_size(cipher));
    if (!result.encrypted_data) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.key);
        free(result.iv);
        return result;
    }
    
    int out_len = 0;
    int final_len = 0;
    
    // Enkriptuj podatke
    if (EVP_EncryptUpdate(ctx, result.encrypted_data, &out_len, data, data_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.encrypted_data);
        free(result.key);
        free(result.iv);
        result.encrypted_data = NULL;
        return result;
    }
    
    // Finalizuj enkripciju
    if (EVP_EncryptFinal_ex(ctx, result.encrypted_data + out_len, &final_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result.encrypted_data);
        free(result.key);
        free(result.iv);
        result.encrypted_data = NULL;
        return result;
    }
    
    result.encrypted_len = out_len + final_len;
    
    // Oslobodi kontekst
    EVP_CIPHER_CTX_free(ctx);
    
    return result;
}