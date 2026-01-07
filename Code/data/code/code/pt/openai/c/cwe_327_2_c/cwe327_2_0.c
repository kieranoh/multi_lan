#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

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
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_data_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = malloc(padded_data_len);
    
    // Prepara o vetor de inicialização
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        result.encrypted_data = NULL;
        return result;
    }

    // Preenche os dados com padding (PKCS#7)
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_data_len - data_len);
    padded_data[data_len] = 0x80;  // Padding para o último byte

    // Inicializa a chave AES com os primeiros 16 bytes da chave fornecida
    AES_set_encrypt_key(key, 128, &aes_key);

    // Aloca espaço para os dados criptografados
    result.encrypted_data = malloc(padded_data_len);
    result.encrypted_len = padded_data_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    result.key = malloc(16);
    
    // Copia a chave usada
    memcpy(result.key, key, 16);
    
    // Criptografa os dados usando AES em modo CBC
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_data_len, &aes_key, iv, AES_ENCRYPT);

    // Copia o IV para o resultado
    memcpy(result.iv, iv, AES_BLOCK_SIZE);

    // Libera a memória temporária
    free(padded_data);

    return result;
}