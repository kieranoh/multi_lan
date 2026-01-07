#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>

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
    if (key.size() < AES_BLOCK_SIZE) {
        throw std::invalid_argument("Key must be at least 16 bytes for AES.");
    }

    // Gerar um IV aleatório
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate IV.");
    }

    // Preparar os dados para criptografia
    std::vector<unsigned char> padded_data = pad_data(data);
    std::vector<unsigned char> encrypted_data(padded_data.size());

    // Criar e configurar o contexto AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(key.data(), 128, &aes_key) < 0) {
        throw std::runtime_error("Failed to set AES encryption key.");
    }

    // Criptografar os dados em modo CBC
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);

    // Retornar o resultado
    encryption_result result;
    result.encrypted_data = std::move(encrypted_data);
    result.iv = std::move(iv);
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + 16); // Usar o primeiro bloco da chave

    return result;
}