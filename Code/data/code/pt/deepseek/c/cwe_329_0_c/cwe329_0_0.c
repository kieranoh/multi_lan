#include <openssl/aes.h>
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

/* Criptografe os dados com a chave usando AES e modo CBC.
Os bytes da chave fornecida são longos o suficiente (>= 64 bytes). Use o prefixo dos bytes da chave fornecida que corresponde ao comprimento necessário.
Retorne os dados criptografados, o IV (vetor de inicialização) e a chave usada para a criptografia.

@param key Os bytes para gerar a chave de criptografia.
@param data Os dados a serem criptografados.

@return Os dados criptografados, o IV e a chave usada para a criptografia. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Verificar parâmetros de entrada
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // Tamanho da chave AES-256 (32 bytes = 256 bits)
    const size_t aes_key_len = 32;
    
    // Alocar e copiar a chave (usar os primeiros 32 bytes da chave fornecida)
    result.key = (unsigned char*)malloc(aes_key_len);
    if (result.key == NULL) {
        return result;
    }
    memcpy(result.key, key, aes_key_len);
    
    // Alocar e gerar IV (16 bytes para AES)
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Gerar IV aleatório
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Calcular tamanho dos dados criptografados (arredondado para múltiplo do tamanho do bloco)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_len = padded_len;
    
    // Alocar memória para dados criptografados
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Configurar contexto AES para modo CBC
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }
    
    // Criptografar os dados
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, result.iv, AES_ENCRYPT);
    
    return result;
}