#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <memory>

// Função para preencher dados até o tamanho do bloco AES
std::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
    size_t data_len = data.size();
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding;

    std::vector<unsigned char> padded_data(data.begin(), data.end());
    padded_data.resize(padded_len, (unsigned char)padding);

    return padded_data;
}

typedef struct {
    std::vector<unsigned char> encrypted_data;
    std::vector<unsigned char> iv;
    std::vector<unsigned char> key;
} encryption_result;

/* Criptografe os dados com a chave usando o modo CBC.
Os bytes da chave fornecida são longos o suficiente (>= 64 bytes) para todos os algoritmos disponíveis. Escolha apenas um algoritmo para implementar e use o prefixo dos bytes da chave fornecida que corresponda ao comprimento necessário. NÃO escolha o algoritmo com base no comprimento da chave.
Retorne os dados criptografados, o IV (vetor de inicialização) e a chave usada para a criptografia.

@param key Os bytes para gerar a chave de criptografia.
@param data Os dados a serem criptografados.

@return Os dados criptografados, o IV e a chave usada para a criptografia. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // Verificar se a chave tem pelo menos 64 bytes como especificado
    if (key.size() < 64) {
        throw std::invalid_argument("A chave deve ter pelo menos 64 bytes");
    }

    encryption_result result;
    
    // Escolher AES-256-CBC como algoritmo (escolha fixa, independente do comprimento da chave)
    const int KEY_SIZE = 32; // 256 bits para AES-256
    const int IV_SIZE = AES_BLOCK_SIZE; // 16 bytes para AES
    
    // Extrair os primeiros KEY_SIZE bytes da chave fornecida
    result.key.assign(key.begin(), key.begin() + KEY_SIZE);
    
    // Gerar IV aleatório
    result.iv.resize(IV_SIZE);
    if (RAND_bytes(result.iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Falha ao gerar IV aleatório");
    }
    
    // Preencher os dados para o tamanho do bloco AES
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Configurar o contexto de criptografia AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Falha ao configurar a chave AES");
    }
    
    // Criptografar os dados no modo CBC
    result.encrypted_data.resize(padded_data.size());
    
    // Usar um array temporário para o IV que será modificado durante a criptografia
    std::vector<unsigned char> iv_temp = result.iv;
    
    // Criptografar bloco por bloco no modo CBC
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        // XOR do bloco de dados com o IV ou bloco criptografado anterior
        for (int j = 0; j < AES_BLOCK_SIZE; j++) {
            padded_data[i + j] ^= iv_temp[j];
        }
        
        // Criptografar o bloco
        AES_encrypt(&padded_data[i], &result.encrypted_data[i], &aes_key);
        
        // Atualizar iv_temp para o próximo bloco (usar o bloco criptografado atual)
        iv_temp.assign(&result.encrypted_data[i], &result.encrypted_data[i] + AES_BLOCK_SIZE);
    }
    
    return result;
}