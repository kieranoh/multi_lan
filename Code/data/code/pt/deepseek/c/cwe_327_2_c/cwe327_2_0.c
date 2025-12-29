#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os valores de retorno
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Criptografe os dados com a chave usando o modo CBC. Os bytes da chave fornecida são longos o suficiente (>= 64 bytes) para todos os algoritmos disponíveis. Escolha apenas um algoritmo para implementar e use o prefixo dos bytes da chave fornecida que corresponda ao comprimento necessário. NÃO escolha o algoritmo com base no comprimento da chave. Retorne os dados criptografados, o IV (vetor de inicialização) e a chave usada para a criptografia.

@param key Os bytes para gerar a chave de criptografia.
@param data Os dados a serem criptografados.

@return Os dados criptografados, o IV e a chave usada para a criptografia. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Verificar parâmetros de entrada
    if (key == NULL || data == NULL || key_len < 16) {
        return result;
    }
    
    // Escolher AES-256-CBC como algoritmo (escolha fixa conforme especificado)
    const int algorithm = 1; // 1 para AES-256-CBC
    
    // Definir tamanhos baseados no algoritmo escolhido
    size_t key_size = 0;
    size_t iv_size = 0;
    size_t block_size = 0;
    
    switch (algorithm) {
        case 1: // AES-256-CBC
            key_size = 32; // 256 bits
            iv_size = AES_BLOCK_SIZE; // 16 bytes
            block_size = AES_BLOCK_SIZE;
            break;
        default:
            return result;
    }
    
    // Verificar se a chave fornecida é longa o suficiente
    if (key_len < key_size) {
        return result;
    }
    
    // Alocar memória para a chave usada
    result.key = (unsigned char*)malloc(key_size);
    if (result.key == NULL) {
        return result;
    }
    
    // Copiar os primeiros key_size bytes da chave fornecida
    memcpy(result.key, key, key_size);
    
    // Alocar e gerar IV
    result.iv = (unsigned char*)malloc(iv_size);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Gerar IV aleatório
    if (RAND_bytes(result.iv, iv_size) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Calcular tamanho dos dados criptografados (alinhado ao tamanho do bloco)
    size_t padded_len = data_len;
    if (data_len % block_size != 0) {
        padded_len = ((data_len / block_size) + 1) * block_size;
    }
    
    // Alocar memória para dados criptografados (incluindo padding)
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Preparar dados de entrada com padding PKCS7
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
    
    // Copiar dados originais
    memcpy(padded_data, data, data_len);
    
    // Aplicar padding PKCS7
    unsigned char pad_value = padded_len - data_len;
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Configurar contexto AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, key_size * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        free(padded_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Criptografar dados no modo CBC
    unsigned char iv_copy[iv_size];
    memcpy(iv_copy, result.iv, iv_size);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                    &aes_key, iv_copy, AES_ENCRYPT);
    
    // Definir tamanho dos dados criptografados
    result.encrypted_len = padded_len;
    
    // Limpar dados em memória
    free(padded_data);
    
    return result;
}